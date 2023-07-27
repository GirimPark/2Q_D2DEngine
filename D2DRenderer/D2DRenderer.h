#pragma once
#include <list>

class D2DRenderer
{
private:
	D2DRenderer();
	~D2DRenderer();

	static D2DRenderer* m_Instance;
public:
	static D2DRenderer* getInstance() { return m_Instance; }

public:
	static ID2D1HwndRenderTarget* m_pD2DRenderTarget;

	// 기본 D2D 사용을 위한 Factory의 인터페이스 포인터
	ID2D1Factory* m_pD2DFactory = NULL;
	// 렌더타겟에서생성한 브러시의 인터페이스 포인터
	ID2D1SolidColorBrush* m_pBrush = NULL;
	// 텍스트 출력을 위한 객체 인터페이스 포인터
	IDWriteFactory* m_pDWriteFactory = NULL;
	IDWriteTextFormat* m_pDWriteTextFormat = NULL;
	// WIC 인터페이스
	IWICImagingFactory* m_pIWICImagingFactory = NULL;

	std::list<std::pair<std::wstring, ID2D1Bitmap*>> m_SharingD2DBitmaps;

public:
	HRESULT Initialize();
	void Finalize();
	HRESULT CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** pID2DBitmap);
	void ReleaseD2DBitmapFromFile(ID2D1Bitmap* pID2D1Bitmap);
};

