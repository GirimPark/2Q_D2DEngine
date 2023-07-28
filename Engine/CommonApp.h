#pragma once
#include "../D2DRenderer/D2DRenderer.h"

#define MAX_LOADSTRING 100
/*---------------------------------------------------------
���ӿ��� ����� �������� ó���� �ϴ� class
������ ���� ������ CommonApp�� ��� �޾� �ΰ����� ó���� �Ѵ�.
----------------------------------------------------------*/
class CommonApp
{
protected:
	D2DRenderer* m_pD2DRenderer = nullptr;
	ID2D1RenderTarget* m_pRenderTarget = nullptr;
	ID2D1SolidColorBrush* m_pBrush = nullptr;
	IDWriteTextFormat* m_pTextFormat = nullptr;

public:
	D2DRenderer*& getRenderer() { return m_pD2DRenderer; }
	ID2D1RenderTarget*& getRenderTarget() { return m_pRenderTarget; }
	ID2D1SolidColorBrush*& getBrush() { return m_pBrush; }
	IDWriteTextFormat*& getTextFormat() { return m_pTextFormat; }

protected:
	CommonApp(HINSTANCE hInstance);
	virtual ~CommonApp();

public:
	static HWND m_hWnd;
	static CommonApp* m_pInstance;	// �� ������ ���ƾ��ϱ� ������ public���� ����

	static float m_deltaTime;

protected:
	HACCEL m_hAccelTable;
	MSG m_msg;
	HINSTANCE m_hInstance;
	WCHAR m_szTitle[MAX_LOADSTRING];                  // ���� ǥ���� �ؽ�Ʈ�Դϴ�.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // �⺻ â Ŭ���� �̸��Դϴ�.
	WNDCLASSEXW m_wcex;
	int m_nCmdShow;

	float m_previousTime;
	float m_currentTime;

public:
	virtual bool Initialize();
	void Loop();
	virtual void Update();
	virtual void Render() abstract;
	virtual void Finalize();

public:
	BOOL GetClientRect(LPRECT lpRect);
	int MessageBoxComError(HRESULT hr);
	void CalculateFrameStats();

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

