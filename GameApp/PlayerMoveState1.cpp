#include "framework.h"
#include "PlayerMoveState1.h"

#include "../Engine/EventManager.h"

PlayerMoveState1::PlayerMoveState1()
{
	AddTransition(&m_MoveToIdle);

	EventManager::GetInstance()->RegisterListener(eEventType::P1TransperMovement, dynamic_cast<EventListener*>(&m_MoveToIdle));
}

void PlayerMoveState1::OnEnter()
{
	framework::EVENT_ANIMATION_INFO animationInfo;
	// error : m_Direction이 {0.f, 0.f}일 때가 존재함
	if (m_Direction.y <= 0.9f)
	{
		animationInfo = { L"MOVE_FRONT", false };
	}
	else if (m_Direction.y >= -0.9f)
	{
		animationInfo = { L"MOVE_BACK", false };
	}
	else if (m_Direction.x >= 0.9f)
	{
		animationInfo = { L"MOVE_SIDE", false };
	}
	else if (m_Direction.x <= -0.9f)
	{
		animationInfo = { L"MOVE_SIDE", true };
	}

	EventManager::GetInstance()->SendEvent(eEventType::P1ChangeAnimation, animationInfo);
}

void PlayerMoveState1::OnStay()
{
	framework::EVENT_ANIMATION_INFO animationInfo;
	if (m_Direction.y <= 0.9f)
	{
		animationInfo = { L"MOVE_FRONT", false };
	}
	else if (m_Direction.y >= -0.9f)
	{
		animationInfo = { L"MOVE_BACK", false };
	}
	else if (m_Direction.x >= 0.9f)
	{
		animationInfo = { L"MOVE_SIDE", false };
	}
	else if (m_Direction.x <= -0.9f)
	{
		animationInfo = { L"MOVE_SIDE", true };
	}

	EventManager::GetInstance()->SendEvent(eEventType::P1KeepAnimation, animationInfo);
}

void PlayerMoveState1::OnExit()
{
	
}
