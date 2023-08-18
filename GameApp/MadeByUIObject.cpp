#include "framework.h"
#include "MadeByUIObject.h"

#include "../Engine/ButtonUI.h"
#include "../Engine/PanelUI.h"
#include "../Engine/EventManager.h"
#include "../Engine/TextureComponent.h"

bool MadeByUIObject::Initialize()
{
	// UI 배치
	m_pMadeByPanel = CreateComponent<PanelUI>(L"StartPanel");
	m_pMadeByPanel->SetWidth(0);
	m_pMadeByPanel->SetHeight(0);
	m_pMadeByPanel->SetColor(D2D1::ColorF::White);
	m_pMadeByPanel->SetRelativeLocation(0.f, 0.f);
	SetRootComponent(m_pMadeByPanel);

	m_pShowPanel = CreateComponent<PanelUI>(L"ShowPanel");
	m_pShowPanel->SetWidth(1700);
	m_pShowPanel->SetHeight(650);
	m_pShowPanel->SetColor(D2D1::ColorF::White);
	m_pShowPanel->SetRelativeLocation(960.f, 465.f);
	m_pShowPanel->SetYIndex(0);
	m_pShowPanel->SetXIndex(0);
	m_pShowPanel->SetActiveUI(false);
	m_pShowPanel->AttachToComponent(m_pMadeByPanel);

	m_pOkayButton = CreateComponent<ButtonUI>(L"SelectButton");
	m_pOkayButton->SetWidth(180.f);
	m_pOkayButton->SetHeight(70.f);
	m_pOkayButton->SetColor(D2D1::ColorF::Red);
	m_pOkayButton->SetRelativeLocation(120.f, 1015.f);
	m_pOkayButton->SetYIndex(3);
	m_pOkayButton->SetXIndex(0);
	m_pOkayButton->SetActiveUI(false);
	m_pOkayButton->AttachToComponent(m_pMadeByPanel);

	m_pCancelButton = CreateComponent<ButtonUI>(L"CancelButton");
	m_pCancelButton->SetWidth(180.f);
	m_pCancelButton->SetHeight(70.f);
	m_pCancelButton->SetColor(D2D1::ColorF::Red);
	m_pCancelButton->SetRelativeLocation(340.f, 1015.f);
	m_pCancelButton->SetYIndex(3);
	m_pCancelButton->SetXIndex(1);
	m_pCancelButton->SetActiveUI(false);
	m_pCancelButton->AttachToComponent(m_pMadeByPanel);

	m_pPrevButton = CreateComponent<ButtonUI>(L"PrevButton");
	m_pPrevButton->SetWidth(390.f);
	m_pPrevButton->SetHeight(110.f);
	m_pPrevButton->SetColor(D2D1::ColorF::Red);
	m_pPrevButton->SetRelativeLocation(960.f, 995.f);
	m_pPrevButton->SetYIndex(0);
	m_pPrevButton->SetXIndex(0);
	m_pPrevButton->SetButtonEventType(eEventType::ChangeWorldToMain);
	m_pPrevButton->AttachToComponent(m_pMadeByPanel);

	m_pPrevTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pPrevTexture->SetTextureAsset(L"../Resource/뒤로2.png", L"GameStartTexture");
	m_pPrevTexture->SetRelativeLocation(0.f, 0.f);
	m_pPrevTexture->AttachToComponent(m_pPrevButton);

	m_pOkayTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pOkayTexture->SetTextureAsset(L"../Resource/Ａ선택.png", L"GameStartTexture");
	m_pOkayTexture->SetRelativeLocation(0.f, 0.f);
	m_pOkayTexture->AttachToComponent(m_pOkayButton);

	m_pCancelTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pCancelTexture->SetTextureAsset(L"../Resource/B선택.png", L"GameStartTexture");
	m_pCancelTexture->SetRelativeLocation(0.f, 0.f);
	m_pCancelTexture->AttachToComponent(m_pCancelButton);

	__super::Initialize();

	return true;
}

void MadeByUIObject::Update(const float deltaTime)
{
	__super::Update(deltaTime);
}