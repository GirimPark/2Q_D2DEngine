#include "pch.h"
#include "UIManager.h"

#include "UI.h"
#include "InputManager.h"
#include "Component.h"
#include "SceneComponent.h"

#include "../GameApp/UIObject.h"

#include <iostream>

UIManager::UIManager()
	: m_pFocusedUI(nullptr)
{
}

void UIManager::Initialize(UIObject* curUI)
{
	m_pCurUI = curUI->GetRootComponent();
}

void UIManager::Update()
{
	// 현재 포커스된 UI 확인
	m_pFocusedUI = GetFocusedUI();

	// 포커스된 UI가 없으면 아무것도 안 하기
	if (!m_pFocusedUI)
	{
		return;
	}

	bool isLbtnClicked = InputManager::GetInstance()->IsKeyPush(eKeyCode::LBUTTON);
	bool isLbtnEnd = InputManager::GetInstance()->IsKeyEnd(eKeyCode::LBUTTON);

	if (m_pFocusedUI != nullptr)
	{
		if(isLbtnClicked)
		{
			m_pFocusedUI->MouseLbtnDown();
			m_pFocusedUI->SetLbtnDown(true);

			printf("됐음\n");
		}
		else if(isLbtnEnd)
		{
			m_pFocusedUI->MouseLbtnUp();

			if (m_pFocusedUI->IsLbtnDown())
			{
				m_pFocusedUI->MouseLbtnClicked();
			}

			m_pFocusedUI->SetLbtnDown(false);
			printf("끝남\n");
		}
	}
}

void UIManager::SetFocusedUI(UI* focusedUI)
{
	if (m_pFocusedUI == focusedUI || nullptr == focusedUI)
	{
		m_pFocusedUI = focusedUI;
		return;
	}

	m_pFocusedUI = focusedUI;
}

UI* UIManager::GetFocusedUI()
{
	std::vector<Component*>& m_pChildUI = m_pCurUI->GetChildrenComponent();

	UI* pFocusedUI = m_pFocusedUI;

	std::vector<Component*>::iterator targetIter = m_pChildUI.end();
	std::vector<Component*>::iterator iter = m_pChildUI.begin();

	for (; iter != m_pChildUI.end(); ++iter)
	{
		if(static_cast<UI*>(*iter)->IsMouseOn())
		{
			targetIter = iter;
			pFocusedUI = static_cast<UI*>(*targetIter);
			pFocusedUI->FocusOn(D2D1::ColorF::Yellow);
			break;
		}
		else if (!(static_cast<UI*>(*iter)->IsMouseOn()) && m_pFocusedUI != nullptr)
		{
			m_pFocusedUI->FocusOut();
		}
	}

	if(targetIter == m_pChildUI.end())
	{
		return nullptr;
	}

	m_pChildUI.erase(targetIter);
	m_pChildUI.push_back(pFocusedUI);

	return pFocusedUI;
}

UI* UIManager::GetTargetedUI(UI* parentUI) const
{
	UI* pTargetUI = nullptr;
	bool isLbtnEnd = InputManager::GetInstance()->IsKeyEnd(eKeyCode::LBUTTON);




	return nullptr;
}