#include "framework.h"
#include "UIObject.h"

#include "../Engine/ButtonUI.h"
#include "../Engine/PanelUI.h"

bool UIObject::Initialize()
{
	m_StartPanel = CreateComponent<PanelUI>(L"StartPanel");
	m_StartPanel->SetWidth(150.f);
	m_StartPanel->SetHeight(300.f);
	m_StartPanel->SetColor(D2D1::ColorF::White);
	m_StartPanel->SetRelativeLocation(ScreenWidth / 4.f, ScreenHeight / 2.f);
	SetRootComponent(m_StartPanel);

	m_pStartButton = CreateComponent<ButtonUI>(L"StartButton");
	m_pStartButton->SetWidth(100.f);
	m_pStartButton->SetHeight(80.f);
	m_pStartButton->SetColor(D2D1::ColorF::Red);
	m_pStartButton->SetBtnFunction(BTN_FUNC::CHANGE_SCENE);
	m_pStartButton->SetRelativeLocation(0.f, -50.f);
	m_pStartButton->AttachToComponent(m_StartPanel);

	m_pMethodButton = CreateComponent<ButtonUI>(L"MethodButton");
	m_pMethodButton->SetWidth(100.f);
	m_pMethodButton->SetHeight(80.f);
	m_pMethodButton->SetColor(D2D1::ColorF::Green);
	m_pMethodButton->SetBtnFunction(BTN_FUNC::PAUSE_UI);
	m_pMethodButton->SetRelativeLocation(0.f, 50.f );
	m_pMethodButton->AttachToComponent(m_StartPanel);

	__super::Initialize();

	return true;
}

void UIObject::Update(const float deltaTime)
{
	//m_StartPanel->Update(deltaTime);
	__super::Update(deltaTime);
}
