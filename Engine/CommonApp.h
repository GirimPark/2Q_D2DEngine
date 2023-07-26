#pragma once

#define MAX_LOADSTRING 100

/*---------------------------------------------------------
���ӿ��� ����� �������� ó���� �ϴ� class
������ ���� ������ CommonApp�� ��� �޾� �ΰ����� ó���� �Ѵ�.
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
	virtual void Render();

public:
	BOOL GetClientRect(LPRECT lpRect);
	int MessageBoxComError(HRESULT hr);
	void CalculateFrameStats();

	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

