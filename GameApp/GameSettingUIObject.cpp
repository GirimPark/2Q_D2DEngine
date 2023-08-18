#include "framework.h"
#include "GameSettingUIObject.h"

#include "../Engine/ButtonUI.h"
#include "../Engine/PanelUI.h"
#include "../Engine/EventManager.h"
#include "../Engine/TextureComponent.h"

bool GameSettingUIObject::Initialize()
{
	// UI 배치
	m_pGameSettingPanel = CreateComponent<PanelUI>(L"GameSettingPanel");
	m_pGameSettingPanel->SetWidth(0);
	m_pGameSettingPanel->SetHeight(0);
	m_pGameSettingPanel->SetColor(D2D1::ColorF::White);
	m_pGameSettingPanel->SetRelativeLocation(0.f, 0.f);
	SetRootComponent(m_pGameSettingPanel);

	m_pMapImage = CreateComponent<PanelUI>(L"MapImagePanel");
	m_pMapImage->SetWidth(940);
	m_pMapImage->SetHeight(520);
	m_pMapImage->SetColor(D2D1::ColorF::Red);
	m_pMapImage->SetRelativeLocation(550.f, 710.f);
	m_pMapImage->SetYIndex(1);
	m_pMapImage->SetXIndex(0);
	m_pMapImage->SetActiveUI(false);
	m_pMapImage->AttachToComponent(m_pGameSettingPanel);

	m_pOkayButton = CreateComponent<ButtonUI>(L"SelectButton");
	m_pOkayButton->SetWidth(180.f);
	m_pOkayButton->SetHeight(70.f);
	m_pOkayButton->SetColor(D2D1::ColorF::Red);
	m_pOkayButton->SetRelativeLocation(120.f, 1015.f);
	m_pOkayButton->SetYIndex(2);
	m_pOkayButton->SetXIndex(0);
	m_pOkayButton->SetActiveUI(false);
	m_pOkayButton->AttachToComponent(m_pGameSettingPanel);

	m_pCancelButton = CreateComponent<ButtonUI>(L"CancelButton");
	m_pCancelButton->SetWidth(180.f);
	m_pCancelButton->SetHeight(70.f);
	m_pCancelButton->SetColor(D2D1::ColorF::Red);
	m_pCancelButton->SetRelativeLocation(340.f, 1015.f);
	m_pCancelButton->SetYIndex(2);
	m_pCancelButton->SetXIndex(1);
	m_pCancelButton->SetActiveUI(false);
	m_pCancelButton->AttachToComponent(m_pGameSettingPanel);

	m_pSelectMap1 = CreateComponent<ButtonUI>(L"SelectMap1");
	m_pSelectMap1->SetWidth(300.f);
	m_pSelectMap1->SetHeight(160.f);
	m_pSelectMap1->SetColor(D2D1::ColorF::White);
	m_pSelectMap1->SetRelativeLocation(230.f, 340.f);
	m_pSelectMap1->SetYIndex(0);
	m_pSelectMap1->SetXIndex(0);
	//m_pSelectMap1->SetButtonEventType(eEventType::ChangeWorldToInGame);
	m_pSelectMap1->AttachToComponent(m_pGameSettingPanel);

	m_pSelectMap2 = CreateComponent<ButtonUI>(L"SelectMap2");
	m_pSelectMap2->SetWidth(300.f);
	m_pSelectMap2->SetHeight(160.f);
	m_pSelectMap2->SetColor(D2D1::ColorF::White);
	m_pSelectMap2->SetRelativeLocation(530.f, 340.f);
	m_pSelectMap2->SetYIndex(0);
	m_pSelectMap2->SetXIndex(1);
	//m_pSelectMap2->SetButtonEventType(eEventType::ChangeWorldToInGame);
	m_pSelectMap2->AttachToComponent(m_pGameSettingPanel);

	m_pSelectMap3 = CreateComponent<ButtonUI>(L"SelectMap3");
	m_pSelectMap3->SetWidth(300.f);
	m_pSelectMap3->SetHeight(160.f);
	m_pSelectMap3->SetColor(D2D1::ColorF::White);
	m_pSelectMap3->SetRelativeLocation(830.f, 340.f);
	m_pSelectMap3->SetYIndex(0);
	m_pSelectMap3->SetXIndex(2);
	//m_pSelectMap3->SetButtonEventType(eEventType::ChangeWorldToInGame);
	m_pSelectMap3->AttachToComponent(m_pGameSettingPanel);

	m_pLeftButton = CreateComponent<ButtonUI>(L"LeftButton");
	m_pLeftButton->SetWidth(60.f);
	m_pLeftButton->SetHeight(60.f);
	m_pLeftButton->SetColor(D2D1::ColorF::White);
	m_pLeftButton->SetRelativeLocation(1150.f, 370.f);
	m_pLeftButton->SetYIndex(0);
	m_pLeftButton->SetXIndex(3);
	//m_pLeftButton->SetButtonEventType(eEventType::ChangeWorldToInGame);
	m_pLeftButton->AttachToComponent(m_pGameSettingPanel);

	m_pRightButton = CreateComponent<ButtonUI>(L"RightButton");
	m_pRightButton->SetWidth(60.f);
	m_pRightButton->SetHeight(60.f);
	m_pRightButton->SetColor(D2D1::ColorF::White);
	m_pRightButton->SetRelativeLocation(1800.f, 370.f);
	m_pRightButton->SetYIndex(0);
	m_pRightButton->SetXIndex(4);
	//m_pRightButton->SetButtonEventType(eEventType::ChangeWorldToInGame);
	m_pRightButton->AttachToComponent(m_pGameSettingPanel);

	m_pStartButton = CreateComponent<ButtonUI>(L"StartButton");
	m_pStartButton->SetWidth(780.f);
	m_pStartButton->SetHeight(110.f);
	m_pStartButton->SetColor(D2D1::ColorF::White);
	m_pStartButton->SetRelativeLocation(1470.f, 970.f);
	m_pStartButton->SetYIndex(1);
	m_pStartButton->SetXIndex(3);
	m_pStartButton->SetButtonEventType(eEventType::ChangeWorldToInGame);
	m_pStartButton->AttachToComponent(m_pGameSettingPanel);

	m_pStartTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pStartTexture->SetTextureAsset(L"../Resource/게임_시작.png", L"GameStartTexture");
	m_pStartTexture->SetRelativeLocation(0.f, 0.f);
	m_pStartTexture->AttachToComponent(m_pStartButton);

	m_pLeftTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pLeftTexture->SetTextureAsset(L"../Resource/화살표(좌).png", L"GameStartTexture");
	m_pLeftTexture->SetRelativeLocation(0.f, 0.f);
	m_pLeftTexture->AttachToComponent(m_pLeftButton);

	m_pRightTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pRightTexture->SetTextureAsset(L"../Resource/화살표(우).png", L"GameStartTexture");
	m_pRightTexture->SetRelativeLocation(0.f, 0.f);
	m_pRightTexture->AttachToComponent(m_pRightButton);

	__super::Initialize();

	return true;
}

void GameSettingUIObject::Update(const float deltaTime)
{
	__super::Update(deltaTime);
}