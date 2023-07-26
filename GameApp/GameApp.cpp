#include "framework.h"
#include "Resource.h"
#include "../D2DRenderer/D2DRenderer.h"
#include "GameApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow) {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: ���⿡ �ڵ带 �Է��մϴ�.
    // Debug Memory Leak Check at start point
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(63680);

    // ���� ���ڿ��� �ʱ�ȭ�մϴ�.
    GameApp App(hInstance);
    App.Initialize();
    App.Loop();

    // Debug Memory Leak Check at end point
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
    _CrtDumpMemoryLeaks();

    return (int)1;
}

GameApp::GameApp(HINSTANCE hInstance)
    :CommonApp::CommonApp(hInstance)
{
    // DemoApp���� ���ҽ��� ���� Ŭ���� �����ϱ�
    LoadStringW(hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_DEMOAPP, m_szWindowClass, MAX_LOADSTRING);

    m_wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DEMOAPP));
    m_wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    m_wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_DEMOAPP);

    m_hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DEMOAPP));
}

GameApp::~GameApp() 
{
}

void GameApp::Update()
{
    // �ð� ���
    __super::Update();

    // World Update

    // FixedUpdate

    // LateUpdate
}

void GameApp::Render()
{
    D2DRenderer::m_pD2DRenderTarget->BeginDraw();

    D2D1::ColorF color(D2D1::ColorF::Black);
    D2DRenderer::m_pD2DRenderTarget->Clear(color);

    // World Render

    D2DRenderer::m_pD2DRenderTarget->EndDraw();
}

bool GameApp::Initialize()
{
    assert(__super::Initialize());

    // World Init

    return false;
}

