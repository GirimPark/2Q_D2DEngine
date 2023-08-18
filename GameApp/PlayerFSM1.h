#pragma once

#include "../Engine/FSM.h"

#include "PlayerIdleState1.h"
#include "PlayerMoveState1.h"

class PlayerFSM1
	: public FSM
{
private:
	PlayerIdleState1 m_IdleState;
	PlayerMoveState1 m_MoveState;

public:
	PlayerFSM1();
};

