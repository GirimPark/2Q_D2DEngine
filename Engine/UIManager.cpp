#include "pch.h"
#include "UIManager.h"

#include "Component.h"
#include "InputManager.h"
#include "SceneComponent.h"
#include "UI.h"

#include "../GameApp/UIObject.h"


UIManager::~UIManager()
{
	m_UILocation.clear();
}

void UIManager::Initialize(const UIObject* curUI)
{
	if(curUI == nullptr)
	{
		return;
	}

	m_pCurUI = curUI->GetRootComponent();
	std::vector<Component*>& m_pChildUI = m_pCurUI->GetChildrenComponent();
	dynamic_cast<UI*>(m_pChildUI[m_childIndex])->FocusOn(D2D1::ColorF::Yellow);

	// ù��° UI focus ���ֱ�
	SetFocusedUI(dynamic_cast<UI*>(m_pChildUI[m_childIndex]));

	// UI ��ġ�� ���ߺ��ͷ� �Ű��ֱ�
	size_t capacity = dynamic_cast<UI*>(m_pChildUI[m_pChildUI.size() - 1])->GetYIndex();

	size_t max = 0;

	for (size_t i = 0; i < m_pChildUI.size(); i++)
	{
		if (max < dynamic_cast<UI*>(m_pChildUI[i])->GetXIndex())
		{
			max = dynamic_cast<UI*>(m_pChildUI[i])->GetXIndex();
		}
	}

	m_UILocation.resize(capacity + 1, std::vector<UI*>(max + 1, nullptr));

	for (size_t i = 0; i < m_pChildUI.size(); i++)
	{
		size_t y = dynamic_cast<UI*>(m_pChildUI[i])->GetYIndex();
		size_t x = dynamic_cast<UI*>(m_pChildUI[i])->GetXIndex();

		m_UILocation[y][x] = dynamic_cast<UI*>(m_pChildUI[i]);
	}
	m_finalControllerPos = { 0.f,0.f };
	m_curControllerPos = { 0.f, 0.f };
}

void UIManager::Update(float deltaTime)
{
	if(m_pCurUI == nullptr)
	{
		return;
	}
	static float timeElapsed = 0.f;
	m_curControllerPos = InputManager::GetInstance()->GetPadAxisLeftThumb(0);

	if (m_finalControllerPos != m_curControllerPos)
	{
		timeElapsed += deltaTime;
	}

	if (timeElapsed >= 0.2f)
	{
		timeElapsed = 0.f;
		m_bChangeFocusState = false;
	}
	else
	{
		if (!m_bChangeFocusState)
		{
			if (m_pFocusedUI != nullptr) // ��Ʈ�ѷ� ����
			{
				if (m_finalControllerPos == m_curControllerPos)
				{
					m_bChangeFocusState = false;
					return;
				}
				m_pFocusedUI = GetFocusedUI();
			}
			m_bChangeFocusState = true;
		}
	}
	return;

	// ���콺
	// ���� ��Ŀ���� UI Ȯ��
	m_pFocusedUI = GetFocusedUI();

	// ��Ŀ���� UI�� ������ �ƹ��͵� �� �ϱ�
	if (!m_pFocusedUI)
	{
		return;
	}

	bool isLbtnClicked = InputManager::GetInstance()->IsKeyPush(eKeyCode::LBUTTON);
	bool isLbtnEnd = InputManager::GetInstance()->IsKeyEnd(eKeyCode::LBUTTON);

	if (m_pFocusedUI != nullptr)
	{
		if (isLbtnClicked)
		{
			m_pFocusedUI->MouseLbtnDown();
			m_pFocusedUI->SetLbtnDown(true);

			printf("����\n");
		}
		else if (isLbtnEnd)
		{
			m_pFocusedUI->MouseLbtnUp();

			if (m_pFocusedUI->IsLbtnDown())
			{
				m_pFocusedUI->MouseLbtnClicked();
			}

			m_pFocusedUI->SetLbtnDown(false);
			printf("����\n");
		}
	}
}

void UIManager::SetFocusedUI(UI* pFocusedUI)
{
	std::vector<Component*>& m_pChildUI = m_pCurUI->GetChildrenComponent();
	m_pFocusedUI = pFocusedUI;
}

UI* UIManager::GetFocusedUI()
{
	// ���콺
	/*std::vector<Component*>& m_pChildUI = m_pCurUI->GetChildrenComponent();

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
	m_pChildUI.push_back(pFocusedUI);*/

	// ��Ʈ�ѷ�
	UI* pFocusedUI = m_pFocusedUI;

	std::vector<Component*>& m_pChildUI = m_pCurUI->GetChildrenComponent();

	float focusedY = m_pFocusedUI->GetFinalPos().y;
	float focusedX = m_pFocusedUI->GetFinalPos().x;


	// y�� ��ȭ���� x�� ��ȭ������ ���� ��
	if (abs(m_curControllerPos.x) < abs(m_curControllerPos.y))
	{
		// ����
		if (m_curControllerPos.y > m_finalControllerPos.y)
		{
			if (m_curY == 0)
			{
				return m_pFocusedUI;
			}
			m_curY -= 1;
		}

		// �Ʒ���
		else if (m_curControllerPos.y < m_finalControllerPos.y)
		{
			if (m_curY == m_UILocation.size() - 1)
			{
				return m_pFocusedUI;
			}
			m_curY += 1;
		}
	}

	// x�� ��ȭ���� y�� ��ȭ������ ���� ��
	else
	{
		// ��������
		if (m_curControllerPos.x < m_finalControllerPos.x)
		{
			if (m_curX == 0)
			{
				return m_pFocusedUI;
			}
			m_curX -= 1;
		}

		// ����������
		else if (m_curControllerPos.x > m_finalControllerPos.x)
		{
			if (m_curX == m_UILocation[0].size() - 1)
			{
				return m_pFocusedUI;
			}
			m_curX += 1;
		}		
	}

	// �� �Ʒ��� �����̱�
	if (m_UILocation[m_curY][m_curX] == nullptr)
	{
		size_t i = 0;
		while (i < m_UILocation[m_curY].size())
		{
			if (i == m_pFocusedUI->GetXIndex())
			{
				i++;
				continue;
			}

			if(m_UILocation[m_curY][i] != nullptr)
			{
				m_curX = i;
				pFocusedUI = m_UILocation[m_curY][m_curX];
				break;
			}
			i++;
		}
	}
	else
	{
		pFocusedUI = m_UILocation[m_curY][m_curX];
	}

	m_pFocusedUI->FocusOut();
	m_curControllerPos = { 0.f, 0.f };
	pFocusedUI->FocusOn(D2D1::ColorF::Yellow);

	return pFocusedUI;
}

// ä��: �� ������ �ϴ� ���ֺ�
UI* UIManager::GetTargetedUI(UI* parentUI) const
{
	UI* pTargetUI = nullptr;
	bool isLbtnEnd = InputManager::GetInstance()->IsKeyEnd(eKeyCode::LBUTTON);




	return nullptr;
}

// InputManager���� ���������� ���� ��ǲ�� ���� ����

