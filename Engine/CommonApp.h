#pragma once
#include "../D2DRenderer/D2DRenderer.h"

#define MAX_LOADSTRING 100
/*---------------------------------------------------------
게임에서 사용할 공통적인 처리를 하는 class
실제로 만들 게임은 CommonApp을 상속 받아 부가적인 처리를 한다.
----------------------------------------------------------*/
class CommonApp
{
protected:
	D2DRenderer* m_pD2DRenderer = nullptr;
	ID2D1HwndRenderTarget* m_pRenderTarget = nullptr;
	ID2D1SolidColorBrush* m_pBrush = nullptr;
	IDWriteTextFormat* m_pTextFormat = nullptr;

public:
	D2DRenderer*& GetRenderer() { return m_pD2DRenderer; }
	ID2D1HwndRenderTarget*& GetRenderTarget() { return m_pRenderTarget; }
	ID2D1SolidColorBrush*& GetBrush() { return m_pBrush; }
	IDWriteTextFormat*& GetTextFormat() { return m_pTextFormat; }

protected:
	CommonApp(HINSTANCE hInstance);
	virtual ~CommonApp();

public:
	static HWND m_hWnd;
	static CommonApp* m_pInstance;	// 매 프레임 돌아야하기 때문에 public으로 선언

	static float m_deltaTime;

protected:
	HACCEL m_hAccelTable;
	MSG m_msg;
	HINSTANCE m_hInstance;
	WCHAR m_szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
	WCHAR m_szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
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

