#include "pch.h"
#include "../Engine/CommonApp.h"
#include "D2DRenderer.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

ID2D1HwndRenderTarget* D2DRenderer::m_pD2DRenderTarget = NULL;
D2DRenderer* D2DRenderer::m_Instance = nullptr;

D2DRenderer::D2DRenderer()
{
    D2DRenderer::m_Instance = this; // 어디서든 렌더러 객체에 접근하기 쉽게 인스턴스를 저장해둔다
}

D2DRenderer::~D2DRenderer()
{
    if (m_pIWICImagingFactory)   m_pIWICImagingFactory->Release();
    if (m_pD2DRenderTarget)  m_pD2DRenderTarget->Release();
    if (m_pD2DFactory)   m_pD2DFactory->Release();

    CoUninitialize();
}

HRESULT D2DRenderer::Initialize()
{
    // COM 사용
    HRESULT hr = S_OK;
    hr = CoInitialize(NULL);
    if (SUCCEEDED(hr))
    {
        // 렌더타겟을 만들수있는팩토리객체를 생성하고 인터페이스 포인터를얻어온다.
        hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &m_pD2DFactory);
    }

    if (SUCCEEDED(hr))
    {
        // 이미 윈도우가만들어진 상태에서 윈도우 사이즈를 구한다.
        RECT rc;
        GetClientRect(CommonApp::m_hWnd, &rc);
        D2D1_SIZE_U size = D2D1::SizeU(
            static_cast<UINT>(rc.right - rc.left),
            static_cast<UINT>(rc.bottom - rc.top)
        );

        // 팩토리로 윈도우핸들, 사이즈를 넘겨 렌더타겟을 만든다.
        hr = m_pD2DFactory->CreateHwndRenderTarget(
            D2D1::RenderTargetProperties(),
            D2D1::HwndRenderTargetProperties(CommonApp::m_hWnd, size),
            &m_pD2DRenderTarget
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &m_pBrush);

    }

    // 텍스트
    if (SUCCEEDED(hr))
    {
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(m_pDWriteFactory),
            reinterpret_cast<IUnknown**>(&m_pDWriteFactory)
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pDWriteFactory->CreateTextFormat(
            L"Bernard MT Condensed", // 
            NULL,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            15.0f,
            L"", //locale
            &m_pDWriteTextFormat
        );
    }

    if (SUCCEEDED(hr))
    {
        // Center the text horizontally and vertically.
        m_pDWriteTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        //m_pDWriteTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    if (SUCCEEDED(hr))
    {
        // 비트맵 출력을 위한 팩토리 생성
        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&m_pIWICImagingFactory)
        );
    }

    if (FAILED(hr))
    {
        _com_error err(hr);
        ::MessageBox(CommonApp::m_hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
    }

    return true;
}

HRESULT D2DRenderer::CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** pID2D1Bitmap)
{
    // 문자열과 포인터 쌍에서 문자열만 같으면 해당 원소를 찾는다.
    auto it = std::find_if(m_SharingD2DBitmaps.begin(), m_SharingD2DBitmaps.end(),
        [strFilePath](std::pair<std::wstring, ID2D1Bitmap*> ContainerData)
        {
            return (ContainerData.first == strFilePath);
        }
    );

    // 찾은 경우
    if (it != m_SharingD2DBitmaps.end())
    {
        *pID2D1Bitmap = it->second;
        (*pID2D1Bitmap)->AddRef();

        return S_OK;
    }

    // 없으면 새로 만든다.
    HRESULT hr;
    // Create a decoder - 디코더를 생성해서 압축을 해제하고 메모리에 올림
    IWICBitmapDecoder* pDecoder = NULL;

    hr = m_pIWICImagingFactory->CreateDecoderFromFilename(
        strFilePath.c_str(),                      // Image to be decoded
        NULL,                            // Do not prefer a particular vendor
        GENERIC_READ,                    // Desired read access to the file
        WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
        &pDecoder                        // Pointer to the decoder
    );

    // Retrieve the first frame of the image from the decoder
    IWICBitmapFrameDecode* pFrame = NULL;
    if (SUCCEEDED(hr))
    {
        hr = pDecoder->GetFrame(0, &pFrame);
    }

    IWICFormatConverter* pConverter = NULL;
    //Step 3: Format convert the frame to 32bppPBGRA
    if (SUCCEEDED(hr))
    {
        // 팩토리를 통해 컨버터를 만든다
        hr = m_pIWICImagingFactory->CreateFormatConverter(&pConverter);
    }

    if (SUCCEEDED(hr))
    {
        // 컨버터를 통해 픽셀 변환
        hr = pConverter->Initialize(
            pFrame,                          // Input bitmap to convert
            GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
            WICBitmapDitherTypeNone,         // Specified dither pattern
            NULL,                            // Specify a particular palette 
            0.f,                             // Alpha threshold
            WICBitmapPaletteTypeCustom       // Palette translation type
        );
    }

    if (SUCCEEDED(hr))
    {
        hr = m_pD2DRenderTarget->CreateBitmapFromWicBitmap(pConverter, NULL, pID2D1Bitmap);
    }

    // 할당 해제
    if (pDecoder != NULL)
        pDecoder->Release();
    if (pFrame != NULL)
        pFrame->Release();
    if (pConverter != NULL)
        pConverter->Release();

    m_SharingD2DBitmaps.push_back(std::make_pair(strFilePath, *pID2D1Bitmap));

    return hr;
}

void D2DRenderer::ReleaseD2DBitmapFromFile(ID2D1Bitmap* pID2D1Bitmap)
{
    ULONG count = pID2D1Bitmap->Release();
    if (count > 0)
        return;

    // 문자열과 포인터 쌍에서 문자열만 같으면 해당 원소를 찾는다.
    auto it = std::find_if(m_SharingD2DBitmaps.begin(), m_SharingD2DBitmaps.end(),
        [pID2D1Bitmap](std::pair<std::wstring, ID2D1Bitmap*> ContainerData)
        {
            return (ContainerData.second == pID2D1Bitmap);
        }
    );

    // 찾은 경우
    if (it != m_SharingD2DBitmaps.end())
    {
        m_SharingD2DBitmaps.erase(it);
    }
}