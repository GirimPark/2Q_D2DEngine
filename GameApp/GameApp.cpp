#include "framework.h"
#include "../Engine/World.h"
#include "TestWorld.h"
#include "GameApp.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Debug Memory Leak Check at start point
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(213);

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
    // GameApp에서 리소스를 얻어와 클래스 설정하기
    LoadStringW(hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_GAMEAPP, m_szWindowClass, MAX_LOADSTRING);

    m_wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMEAPP));
    m_wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));
    m_wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    m_wcex.lpszMenuName = MAKEINTRESOURCEW(IDI_GAMEAPP);

    m_hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDI_GAMEAPP));
}

GameApp::~GameApp()
{
   
}

void GameApp::Update()
{
    // 시간 계산
    __super::Update();

    // Test
    m_pTestWorld->Update();

    // Manager Update
    // FixedUpdate
    // LateUpdate
}

void GameApp::Render()
{
    m_pD2DRenderer->getRenderTarget()->BeginDraw();

    D2D1::ColorF color(D2D1::ColorF::Black);
    m_pD2DRenderer->getRenderTarget()->Clear(color);

    // WorldManager -> World -> GameObject -> Component로 renderTarget(m_pRenderer) 내려보내기
    // Test
    m_pTestWorld->Render();
    // WorldManager Render

    m_pD2DRenderer->getRenderTarget()->EndDraw();
}

bool GameApp::Initialize()
{
    assert(__super::Initialize());

    // Test
    m_pTestWorld = new TestWorld;
    m_pTestWorld->Initialize();
    // WorldManager Init

    return false;
}

void GameApp::Finalize()
{
  
    // World Finalize ?
    delete m_pTestWorld;
    __super::Finalize();
}

