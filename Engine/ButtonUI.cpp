#include "pch.h"
#include "ButtonUI.h"

#include "CommonApp.h"
#include "InputManager.h"

bool ButtonUI::Initialize()
{
	bool res = __super::Initialize();
	assert(res);

	m_finalUIPos.x = this->GetWorldLocation().x;
	m_finalUIPos.y = this->GetWorldLocation().y;

	return true;
}

void ButtonUI::Update(const float deltaTime)
{
	__super::Update(deltaTime);
	// todo(채원): 버튼을 만든 만큼 Update를 돌기 때문에 이 부분은 매니저에서 고치자
	if (InputManager::GetInstance()->IsKeyPush(LBUTTON))
	{
		if(IsMouseOn())
		{
			MouseLbtnClicked();
		}
	}
}

void ButtonUI::Render(ID2D1RenderTarget* pRenderTarget)
{
	CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);
	m_FinalTransform = m_WorldTransform * GetCameraTransform();
	pRenderTarget->SetTransform(m_FinalTransform);
	pRenderTarget->DrawRectangle(
		D2D1::RectF(-m_Width / 2, -m_Height / 2, m_Width / 2, m_Height / 2),
		CommonApp::m_pInstance->GetBrush(),
		2.f);
}

void ButtonUI::SetBtnFunction(BTN_FUNC _func)
{
	m_function = _func;
}

void ButtonUI::MouseLbtnClicked()
{
	switch (m_function)
	{
	case BTN_FUNC::CHANGE_SCENE:
	{
		printf("CHANGE_SCENE 실행된다\n");
	}
	break;
	case BTN_FUNC::PAUSE_UI:
	{
		printf("PAUSE_UI 실행된다\n");
		break;
	}
	case BTN_FUNC::DELTE_PARENT_UI:
	{

	}
	default:
		break;
	}
	
}
