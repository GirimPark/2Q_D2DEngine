#include "framework.h"
#include "InstructionUIObject.h"

#include "../Engine/ButtonUI.h"
#include "../Engine/PanelUI.h"
#include "../Engine/EventManager.h"
#include "../Engine/TextureComponent.h"

bool InstructionUIObject::Initialize()
{
	// UI 배치
	m_pInstructionWorldPanel = CreateComponent<PanelUI>(L"InstructionPanel");
	m_pInstructionWorldPanel->SetWidth(0);
	m_pInstructionWorldPanel->SetHeight(0);
	m_pInstructionWorldPanel->SetColor(D2D1::ColorF::White);
	m_pInstructionWorldPanel->SetRelativeLocation(0.f, 0.f);
	SetRootComponent(m_pInstructionWorldPanel);

	m_pShowPanel = CreateComponent<PanelUI>(L"ShowPanel");
	m_pShowPanel->SetWidth(1200);
	m_pShowPanel->SetHeight(900);
	m_pShowPanel->SetColor(D2D1::ColorF::White);
	m_pShowPanel->SetRelativeLocation(650.f, 500.f);
	m_pShowPanel->SetYIndex(0);
	m_pShowPanel->SetXIndex(0);
	m_pShowPanel->SetActiveUI(false);
	m_pShowPanel->AttachToComponent(m_pInstructionWorldPanel);

	m_pOkayButton = CreateComponent<ButtonUI>(L"OkayButton");
	m_pOkayButton->SetWidth(180.f);
	m_pOkayButton->SetHeight(70.f);
	m_pOkayButton->SetColor(D2D1::ColorF::Red);
	m_pOkayButton->SetRelativeLocation(120.f, 1015.f);
	m_pOkayButton->SetYIndex(3);
	m_pOkayButton->SetXIndex(0);
	m_pOkayButton->SetActiveUI(false);
	m_pOkayButton->AttachToComponent(m_pInstructionWorldPanel);

	m_pCancelButton = CreateComponent<ButtonUI>(L"CancelButton");
	m_pCancelButton->SetWidth(180.f);
	m_pCancelButton->SetHeight(70.f);
	m_pCancelButton->SetColor(D2D1::ColorF::Red);
	m_pCancelButton->SetRelativeLocation(340.f, 1015.f);
	m_pCancelButton->SetYIndex(3);
	m_pCancelButton->SetXIndex(1);
	m_pCancelButton->SetActiveUI(false);
	m_pCancelButton->AttachToComponent(m_pInstructionWorldPanel);

	m_pInstructionButton = CreateComponent<ButtonUI>(L"InstructionButton");
	m_pInstructionButton->SetWidth(390.f);
	m_pInstructionButton->SetHeight(110.f);
	m_pInstructionButton->SetColor(D2D1::ColorF::White);
	m_pInstructionButton->SetRelativeLocation(1595.f, 575.f);
	m_pInstructionButton->SetYIndex(0);
	m_pInstructionButton->SetXIndex(2);
	m_pInstructionButton->SetButtonEventType(eEventType::ChangeWorldToInstruction);
	m_pInstructionButton->AttachToComponent(m_pInstructionWorldPanel);

	m_pControllerButton = CreateComponent<ButtonUI>(L"MadeByButton");
	m_pControllerButton->SetWidth(390.f);
	m_pControllerButton->SetHeight(110.f);
	m_pControllerButton->SetColor(D2D1::ColorF::White);
	m_pControllerButton->SetRelativeLocation(1595.f, 715.f);
	m_pControllerButton->SetYIndex(1);
	m_pControllerButton->SetXIndex(2);
	//m_pControllerButton->SetButtonEventType(eEventType::ChangeWorldToMadeBy);
	m_pControllerButton->AttachToComponent(m_pInstructionWorldPanel);

	m_pKeyBoardButton = CreateComponent<ButtonUI>(L"MadeByButton");
	m_pKeyBoardButton->SetWidth(390.f);
	m_pKeyBoardButton->SetHeight(110.f);
	m_pKeyBoardButton->SetColor(D2D1::ColorF::White);
	m_pKeyBoardButton->SetRelativeLocation(1595.f, 855.f);
	m_pKeyBoardButton->SetYIndex(2);
	m_pKeyBoardButton->SetXIndex(2);
	//m_pKeyBoardButton->SetButtonEventType(eEventType::ChangeWorldToMadeBy);
	m_pKeyBoardButton->AttachToComponent(m_pInstructionWorldPanel);

	m_pPrevButton = CreateComponent<ButtonUI>(L"ExitButton");
	m_pPrevButton->SetWidth(390.f);
	m_pPrevButton->SetHeight(110.f);
	m_pPrevButton->SetColor(D2D1::ColorF::White);
	m_pPrevButton->SetRelativeLocation(1595.f, 995.f);
	m_pPrevButton->SetYIndex(3);
	m_pPrevButton->SetXIndex(2);
	m_pPrevButton->SetButtonEventType(eEventType::ChangeWorldToMain);
	m_pPrevButton->AttachToComponent(m_pInstructionWorldPanel);

	m_pPrevTexture = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pPrevTexture->SetTextureAsset(L"../Resource/뒤로2.png", L"GameStartTexture");
	m_pPrevTexture->SetRelativeLocation(0.f, 0.f);
	m_pPrevTexture->AttachToComponent(m_pPrevButton);

	__super::Initialize();

	return true;
}

void InstructionUIObject::Update(const float deltaTime)
{
	__super::Update(deltaTime);
}