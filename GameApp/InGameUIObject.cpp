#include "framework.h"
#include "InGameUIObject.h"

#include "../Engine/ButtonUI.h"
#include "../Engine/PanelUI.h"
#include "../Engine/EventManager.h"
#include "../Engine/TextureComponent.h"

bool InGameUIObject::Initialize()
{
	// UI 배치
	m_pInGamePanel = CreateComponent<PanelUI>(L"InGamePanel");
	m_pInGamePanel->SetWidth(0);
	m_pInGamePanel->SetHeight(0);
	m_pInGamePanel->SetColor(D2D1::ColorF::White);
	m_pInGamePanel->SetRelativeLocation(0.f, 0.f);
	SetRootComponent(m_pInGamePanel);

	m_pGoalMoneyPanel = CreateComponent<PanelUI>(L"GoalMoneyPanel");
	m_pGoalMoneyPanel->SetWidth(1100.f);
	m_pGoalMoneyPanel->SetHeight(30.f);
	m_pGoalMoneyPanel->SetColor(D2D1::ColorF::Red);
	m_pGoalMoneyPanel->SetRelativeLocation(960.f, 35.f);
	m_pGoalMoneyPanel->SetYIndex(3);
	m_pGoalMoneyPanel->SetXIndex(0);
	m_pGoalMoneyPanel->SetActiveUI(false);
	m_pGoalMoneyPanel->AttachToComponent(m_pInGamePanel);

	m_Player1Item = CreateComponent<PanelUI>(L"Player1Item");
	m_Player1Item->SetWidth(350.f);
	m_Player1Item->SetHeight(120.f);
	m_Player1Item->SetColor(D2D1::ColorF::Red);
	m_Player1Item->SetRelativeLocation(195.f, 80.f);
	m_Player1Item->SetYIndex(3);
	m_Player1Item->SetXIndex(0);
	m_Player1Item->SetActiveUI(false);
	m_Player1Item->AttachToComponent(m_pInGamePanel);

	m_Player2Item = CreateComponent<PanelUI>(L"Player2Item");
	m_Player2Item->SetWidth(350.f);
	m_Player2Item->SetHeight(120.f);
	m_Player2Item->SetColor(D2D1::ColorF::Red);
	m_Player2Item->SetRelativeLocation(1725.f, 80.f);
	m_Player2Item->SetYIndex(3);
	m_Player2Item->SetXIndex(0);
	m_Player2Item->SetActiveUI(false);
	m_Player2Item->AttachToComponent(m_pInGamePanel);

	m_Player3Item = CreateComponent<PanelUI>(L"Player3Item");
	m_Player3Item->SetWidth(350.f);
	m_Player3Item->SetHeight(120.f);
	m_Player3Item->SetColor(D2D1::ColorF::Red);
	m_Player3Item->SetRelativeLocation(195.f, 980.f);
	m_Player3Item->SetYIndex(3);
	m_Player3Item->SetXIndex(0);
	m_Player3Item->SetActiveUI(false);
	m_Player3Item->AttachToComponent(m_pInGamePanel);

	m_Player4Item = CreateComponent<PanelUI>(L"Player4Item");
	m_Player4Item->SetWidth(350.f);
	m_Player4Item->SetHeight(120.f);
	m_Player4Item->SetColor(D2D1::ColorF::Red);
	m_Player4Item->SetRelativeLocation(1725.f, 980.f);
	m_Player4Item->SetYIndex(3);
	m_Player4Item->SetXIndex(0);
	m_Player4Item->SetActiveUI(false);
	m_Player4Item->AttachToComponent(m_pInGamePanel);

	m_pItemTexture1 = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pItemTexture1->SetTextureAsset(L"../Resource/아이템보관창_빨강.png", L"GameStartTexture");
	m_pItemTexture1->SetRelativeLocation(0.f, 0.f);
	m_pItemTexture1->AttachToComponent(m_Player1Item);

	m_pItemTexture2 = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pItemTexture2->SetTextureAsset(L"../Resource/아이템보관창_파랑.png", L"GameStartTexture");
	m_pItemTexture2->SetRelativeLocation(0.f, 0.f);
	m_pItemTexture2->AttachToComponent(m_Player2Item);

	m_pItemTexture3 = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pItemTexture3->SetTextureAsset(L"../Resource/아이템보관창_노랑.png", L"GameStartTexture");
	m_pItemTexture3->SetRelativeLocation(0.f, 0.f);
	m_pItemTexture3->AttachToComponent(m_Player3Item);

	m_pItemTexture4 = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pItemTexture4->SetTextureAsset(L"../Resource/아이템보관창_초록.png", L"GameStartTexture");
	m_pItemTexture4->SetRelativeLocation(0.f, 0.f);
	m_pItemTexture4->AttachToComponent(m_Player4Item);


	__super::Initialize();

	return true;
}

void InGameUIObject::Update(const float deltaTime)
{
	__super::Update(deltaTime);
}