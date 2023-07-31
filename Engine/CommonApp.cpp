#include "pch.h"
#include "CommonApp.h"

#ifdef FRAMEWORK_DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

CommonApp* CommonApp::m_pInstance = nullptr;
HWND CommonApp::m_hWnd;
float CommonApp::m_deltaTime = 0.f;

LRESULT CALLBACK DefaultWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return CommonApp::m_pInstance->WndProc(hWnd, message, wParam, lParam);
}

CommonApp::CommonApp(HINSTANCE hInstance)
    : m_hInstance(hInstance)
    , m_szWindowClass(L"DefaultWindowClass")
    , m_szTitle(L"CommonApp")
{
    std::wstring str(__FUNCTIONW__);
    str += L"\n";
    OutputDebugString(str.c_str());

    CommonApp::m_pInstance = this;

    m_wcex.hInstance = hInstance;
    m_wcex.cbSize = sizeof(WNDCLASSEX);
    m_wcex.style = CS_HREDRAW | CS_VREDRAW;
    m_wcex.lpfnWndProc = DefaultWndProc;
    m_wcex.cbClsExtra = 0;
    m_wcex.cbWndExtra = 0;
    m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    m_wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    m_wcex.lpszClassName = m_szWindowClass;

    // 렌더러 생성
    m_pD2DRenderer = new D2DRenderer;
}

CommonApp::~CommonApp()
{
    std::wstring str(__FUNCTIONW__);
    str += L"\n";
    OutputDebugString(str.c_str());
}

// 윈도우 정보는 게임마다 다르기 때문에 윈도우 등록, 생성, 보이기만 한다.
bool CommonApp::Initialize()
{
    // 등록
    RegisterClassExW(&m_wcex);

    RECT rt = { 0, 0, ScreenWidth, ScreenHeight };
    AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true);
    // 생성
    m_hWnd = CreateWindowW(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW,
        100, 100,               // 시작 위치
        rt.right - rt.left, rt.bottom - rt.top,    // 가로, 세로
        nullptr, nullptr, m_hInstance, nullptr);

    if (!m_hWnd)
    {
        return false;
    }

    // 윈도우 보이기
    ShowWindow(m_hWnd, SW_SHOW);
    UpdateWindow(m_hWnd);

    // Time
    m_currentTime = m_previousTime = (float)GetTickCount64() / 1000.f;

    // 렌더러 등록
    HRESULT hr = m_pD2DRenderer->Initialize();
    if (FAILED(hr))
    {
        MessageBoxComError(hr);
    }
    m_pRenderTarget = m_pD2DRenderer->GetRenderTarget();
    m_pBrush = m_pD2DRenderer->GetBrush();
    m_pTextFormat = m_pD2DRenderer->GetTextFormat();

    return true;
}

void CommonApp::Loop()
{
    while (true)
    {
        if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
        {
            if (m_msg.message == WM_QUIT)
                break;

            if (!TranslateAccelerator(m_msg.hwnd, m_hAccelTable, &m_msg))
            {
                TranslateMessage(&m_msg);
                DispatchMessage(&m_msg);
            }
        }
        else
        {
            Update();
            Render();
        }
    }
    Finalize();
}

void CommonApp::Update()
{
    m_previousTime = m_currentTime;
    m_currentTime = (float)GetTickCount64() / 1000.f;
    m_deltaTime = m_currentTime - m_previousTime;
    CalculateFrameStats();
}

void CommonApp::Finalize()
{
    delete m_pD2DRenderer;
}

BOOL CommonApp::GetClientRect(LPRECT lpRect)
{
    return ::GetClientRect(m_hWnd, lpRect);
}

int CommonApp::MessageBoxComError(HRESULT hr)
{
    _com_error err(hr);
    return ::MessageBox(m_hWnd, err.ErrorMessage(), L"FAILED", MB_OK);
}

void CommonApp::CalculateFrameStats()
{
    // FPS 계산, 제목표시줄에 출력
    static int frameCnt = -1;
    static float timeElapsed = 0.f;

    frameCnt++;
    if (frameCnt == 0)
        return;

    timeElapsed += m_deltaTime;

    // FPS의 평균 계산
    if (timeElapsed >= 1.0f)
    {
        float fps = (float)frameCnt;
        fps = (float)frameCnt;
        float spf = 1000.f / fps;

        std::wstring windowText;
        windowText.append(m_szTitle);
        windowText.append(L"   FPS: ");
        windowText.append(std::to_wstring(fps));
        windowText.append(L"   SPF: ");
        windowText.append(std::to_wstring(spf));
        SetWindowText(m_hWnd, windowText.c_str());

        frameCnt = 0;
        timeElapsed -= 1.0f;
    }
}

LRESULT CommonApp::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    return 0;
}

