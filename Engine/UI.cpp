#include "pch.h"
#include "UI.h"

#include "InputManager.h"
#include "CommonApp.h"

bool UI::Initialize()
{
	bool res = SceneComponent::Initialize();
	assert(res);

	return true;
}

void UI::Update(const float deltaTime)
{
	CheckMouseOn();
	if(m_bMouseOn)
	{
		//printf("UI �ȿ� ����\n");
	}
}

void UI::Render(ID2D1RenderTarget* pRenderTarget)
{
}

void UI::AddChildUI(UI* childUI)
{
	m_childUI.push_back(childUI);
	childUI->m_parentUI = this;
}

void UI::CheckMouseOn()
{
	const float mouseX = InputManager::GetInstance()->GetMousePos().x;
	const float mouseY = InputManager::GetInstance()->GetMousePos().y;

	if (mouseX > m_finalUIPos.x - (m_Width / 2) && mouseX < m_finalUIPos.x + (m_Width / 2)
		&& mouseY > m_finalUIPos.y - (m_Height / 2) && mouseY < (m_Height / 2) + m_finalUIPos.y)
	{
		m_bMouseOn = true;
		return;
	}
	m_bMouseOn = false;
}
