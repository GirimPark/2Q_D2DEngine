#pragma once
#include <list>

/*----------------------------------------------------------------------
Renderer�� �̱������� ������ �ʱ����� �̱����� CommonApp(Core)�� Ȱ���Ѵ�.
GameApp �ܿ����� �������� ���縦 ����� �ϰ�,
Engine������ �������� ���縦 �ȴ�.
-----------------------------------------------------------------------*/
class D2DRenderer
{
public:
	~D2DRenderer();

private:
	ID2D1HwndRenderTarget* m_pD2DRenderTarget;

	// �⺻ D2D ����� ���� Factory�� �������̽� ������
	ID2D1Factory* m_pD2DFactory = NULL;
	// ����Ÿ�ٿ��������� �귯���� �������̽� ������
	ID2D1SolidColorBrush* m_pBrush = NULL;
	// �ؽ�Ʈ ����� ���� ��ü �������̽� ������
	IDWriteFactory* m_pDWriteFactory = NULL;
	IDWriteTextFormat* m_pDWriteTextFormat = NULL;
	// WIC �������̽�
	IWICImagingFactory* m_pIWICImagingFactory = NULL;

	std::list<std::pair<std::wstring, ID2D1Bitmap*>> m_SharingD2DBitmaps;

public:
	ID2D1HwndRenderTarget*& getRenderTarget() { return m_pD2DRenderTarget; }
	ID2D1SolidColorBrush*& getBrush() { return m_pBrush; }
	IDWriteTextFormat*& getTextFormat() { return m_pDWriteTextFormat; }

	HRESULT Initialize();
	HRESULT CreateD2DBitmapFromFile(std::wstring strFilePath, ID2D1Bitmap** pID2DBitmap);
	void ReleaseD2DBitmapFromFile(ID2D1Bitmap* pID2D1Bitmap);
};

