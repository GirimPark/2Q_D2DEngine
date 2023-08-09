#include "framework.h"
#include "GameApp.h"

#include "Resource.h"
#include "ChaeWorld.h"
#include "TestWorld.h"
#include "JunWorld.h"

#include "../Engine/EventManager.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Debug Memory Leak Check at start point
    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(424);

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
    :CommonApp(hInstance)
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
    __super::Update();

    m_pTestWorld->Update(m_pTimeManager.GetDeltaTime());
    // 월드매니저까지 CommonApp Update로 편입되면 EventManager도 같이 넣을 수 있을듯
    EventManager::GetInstance()->Update();
    // Manager Update
    // FixedUpdate
    // LateUpdate
}

void GameApp::Render()
{
    m_pRenderTarget->BeginDraw();

    D2D1::ColorF color(D2D1::ColorF::Black);
    m_pRenderTarget->Clear(color);

    // Test
    m_pTestWorld->Render();
    // WorldManager Render

    m_pRenderTarget->EndDraw();
}

bool GameApp::Initialize()
{
    bool res = __super::Initialize();
    assert(res);

    // Test
	//m_pTestWorld = new TestWorld;
    // m_pTestWorld->Initialize();

    m_pTestWorld = new JunWorld;
    //m_pTestWorld = new ChaeWorld;
    m_pTestWorld->Initialize();

    EventManager::GetInstance()->Initialize();

    // WorldManager Init

    return false;
}

void GameApp::Finalize()
{
    // World Finalize ?
    delete m_pTestWorld;
    EventManager::GetInstance()->Finalize();
    __super::Finalize();
}

