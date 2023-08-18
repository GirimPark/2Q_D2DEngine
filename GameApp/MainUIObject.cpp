#include "framework.h"
#include "MainUIObject.h"

#include "../Engine/ButtonUI.h"
#include "../Engine/PanelUI.h"
#include "../Engine/EventManager.h"
#include "../Engine/TextureComponent.h"

bool MainUIObject::Initialize()
{
	// UI 배치
	m_pMainWorldPanel = CreateComponent<PanelUI>(L"StartPanel");
	m_pMainWorldPanel->SetWidth(0);
	m_pMainWorldPanel->SetHeight(0);
	m_pMainWorldPanel->SetColor(D2D1::ColorF::White);
	m_pMainWorldPanel->SetRelativeLocation(0.f, 0.f);
	SetRootComponent(m_pMainWorldPanel);

	m_pOkayButton = CreateComponent<ButtonUI>(L"SelectButton");
	m_pOkayButton->SetWidth(180.f);
	m_pOkayButton->SetHeight(70.f);
	m_pOkayButton->SetColor(D2D1::ColorF::Red);
	m_pOkayButton->SetRelativeLocation(120.f, 1015.f);
	m_pOkayButton->SetYIndex(3);
	m_pOkayButton->SetXIndex(0);
	m_pOkayButton->SetActiveUI(false);
	m_pOkayButton->AttachToComponent(m_pMainWorldPanel);

	m_pCancelButton = CreateComponent<ButtonUI>(L"CancelButton");
	m_pCancelButton->SetWidth(180.f);
	m_pCancelButton->SetHeight(70.f);
	m_pCancelButton->SetColor(D2D1::ColorF::Red);
	m_pCancelButton->SetRelativeLocation(340.f, 1015.f);
	m_pCancelButton->SetYIndex(3);
	m_pCancelButton->SetXIndex(1);
	m_pCancelButton->SetActiveUI(false);
	m_pCancelButton->AttachToComponent(m_pMainWorldPanel);

	m_pStartButton = CreateComponent<ButtonUI>(L"StartButton");
	m_pStartButton->SetWidth(390.f);
	m_pStartButton->SetHeight(110.f);
	m_pStartButton->SetColor(D2D1::ColorF::White);
	m_pStartButton->SetRelativeLocation(1595.f, 575.f);
	m_pStartButton->SetYIndex(0);
	m_pStartButton->SetXIndex(2);
	m_pStartButton->SetButtonEventType(eEventType::ChangeWorldToGameSetting);
	m_pStartButton->AttachToComponent(m_pMainWorldPanel);

	m_pInstructionButton = CreateComponent<ButtonUI>(L"InstructionButton");
	m_pInstructionButton->SetWidth(390.f);
	m_pInstructionButton->SetHeight(110.f);
	m_pInstructionButton->SetColor(D2D1::ColorF::White);
	m_pInstructionButton->SetRelativeLocation(1595.f, 715.f);
	m_pInstructionButton->SetYIndex(1);
	m_pInstructionButton->SetXIndex(2);
	m_pInstructionButton->SetButtonEventType(eEventType::ChangeWorldToInstruction);
	m_pInstructionButton->AttachToComponent(m_pMainWorldPanel);

	m_pMadeByButton = CreateComponent<ButtonUI>(L"MadeByButton");
	m_pMadeByButton->SetWidth(390.f);
	m_pMadeByButton->SetHeight(110.f);
	m_pMadeByButton->SetColor(D2D1::ColorF::White);
	m_pMadeByButton->SetRelativeLocation(1595.f, 855.f);
	m_pMadeByButton->SetYIndex(2);
	m_pMadeByButton->SetXIndex(2);
	m_pMadeByButton->SetButtonEventType(eEventType::ChangeWorldToMadeBy);
	m_pMadeByButton->AttachToComponent(m_pMainWorldPanel);

	m_pExitButton = CreateComponent<ButtonUI>(L"ExitButton");
	m_pExitButton->SetWidth(390.f);
	m_pExitButton->SetHeight(110.f);
	m_pExitButton->SetColor(D2D1::ColorF::White);
	m_pExitButton->SetRelativeLocation(1595.f, 995.f);
	m_pExitButton->SetYIndex(3);
	m_pExitButton->SetXIndex(2);
	// todo (채원): 끝내는 이벤트 해줘야함.
	m_pExitButton->AttachToComponent(m_pMainWorldPanel);

	// 텍스처 입히기
	m_pOkayTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pOkayTexture->SetTextureAsset(L"../Resource/Ａ선택.png", L"GameStartTexture");
	m_pOkayTexture->SetRelativeLocation(0.f, 0.f);
	m_pOkayTexture->AttachToComponent(m_pOkayButton);

	m_pCancelTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pCancelTexture->SetTextureAsset(L"../Resource/B선택.png", L"GameStartTexture");
	m_pCancelTexture->SetRelativeLocation(0.f, 0.f);
	m_pCancelTexture->AttachToComponent(m_pCancelButton);

	m_pGameStartTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pGameStartTexture->SetTextureAsset(L"../Resource/게임_시작.png", L"GameStartTexture");
	m_pGameStartTexture->SetRelativeLocation(0.f, 0.f);
	m_pGameStartTexture->AttachToComponent(m_pStartButton);

	m_pInstructionTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pInstructionTexture->SetTextureAsset(L"../Resource/게임방법.png", L"GameStartTexture");
	m_pInstructionTexture->SetRelativeLocation(0.f, 0.f);
	m_pInstructionTexture->AttachToComponent(m_pInstructionButton);

	m_pMadeByTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pMadeByTexture->SetTextureAsset(L"../Resource/제작.png", L"GameStartTexture");
	m_pMadeByTexture->SetRelativeLocation(0.f, 0.f);
	m_pMadeByTexture->AttachToComponent(m_pMadeByButton);

	m_pExitTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pExitTexture->SetTextureAsset(L"../Resource/끝내기2.png", L"GameStartTexture");
	m_pExitTexture->SetRelativeLocation(0.f, 0.f);
	m_pExitTexture->AttachToComponent(m_pExitButton);

	__super::Initialize();

	return true;
}

void MainUIObject::Update(const float deltaTime)
{
	__super::Update(deltaTime);
}