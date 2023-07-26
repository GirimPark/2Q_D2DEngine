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

    // TODO: 여기에 코드를 입력합니다.
    // Debug Memory Leak Check at start point
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(63680);

    // 전역 문자열을 초기화합니다.
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
    // DemoApp에서 리소스를 얻어와 클래스 설정하기
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
    // 시간 계산
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

