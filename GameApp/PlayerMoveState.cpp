#include "framework.h"
#include "PlayerMoveState.h"

#include "PlayerTransition.h"

#include "../Engine/EventManager.h"

PlayerMoveState::PlayerMoveState()
{
	AddTransition(&m_MoveToIdle);

	EventManager::GetInstance()->RegisterListener(eEventType::TransperMovement, dynamic_cast<EventListener*>(&m_MoveToIdle));
}

void PlayerMoveState::OnEnter()
{
	// MoveAnimation Àç»ý
	framework::EVENT_ANIMATION_INFO animationInfo = { L"MOVE", m_bFlip };
	EventManager::GetInstance()->SendEvent(eEventType::ChangeCurAnimation, animationInfo);
}

void PlayerMoveState::OnExit()
{
}