#pragma once

#include "../Engine/FSM.h"
#include "../Engine/EventListener.h"
#include "PlayerIdleState.h"
#include "PlayerMoveState.h"

class PlayerFSM
	: public FSM
	, public EventListener
{
private:
	PlayerIdleState m_IdleState;
	PlayerMoveState m_MoveState;

public:
	PlayerFSM();

	void HandleEvent(Event* event) final;
};

