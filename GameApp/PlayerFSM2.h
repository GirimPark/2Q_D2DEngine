#pragma once

#include "../Engine/FSM.h"

#include "PlayerIdleState2.h"
#include "PlayerMoveState2.h"

class PlayerFSM2
	: public FSM
{
private:
	PlayerIdleState2 m_IdleState;
	PlayerMoveState2 m_MoveState;

public:
	PlayerFSM2();
};

