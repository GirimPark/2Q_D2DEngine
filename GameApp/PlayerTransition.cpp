#include "framework.h"
#include "PlayerTransition.h"

#include "../Engine/Event.h"
#include "../Engine/EventManager.h"

void PlayerTransition::HandleEvent(Event* event)
{
	if(event->eventID == eEventType::TransperMovement)
	{
		m_bMoving = event->movementInfo.isMoving;
		m_LookDirection = event->movementInfo.lookDirection;
	}
}
