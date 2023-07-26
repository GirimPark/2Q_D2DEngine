#pragma once

#define MAX_LOADSTRING 100

/*---------------------------------------------------------
게임에서 사용할 공통적인 처리를 하는 class
실제로 만들 게임은 CommonApp을 상속 받아 부가적인 처리를 한다.
----------------------------------------------------------*/
class CommonApp
{
protected:
	CommonApp(HINSTANCE hInstance);
	virtual ~CommonApp();

public:
	static CommonApp* m_pInstance;

	static HWND m_hWnd;
	static float m_deltaTime;
	static float m_nWidth;
	static float m_nHeight;

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
	virtual void Render();

public:
	BOOL GetClientRect(LPRECT lpRect);
	int MessageBoxComError(HRESULT hr);
	void CalculateFrameStats();

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

