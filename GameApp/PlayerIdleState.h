#pragma once

#include "../Engine/FSMState.h"
#include "PlayerTransition.h"

class PlayerIdleState
	: public FSMState
{
private:
	IdleToMove m_IdleToMove;

public:
	PlayerIdleState();

public:
	virtual void OnEnter() override final;
	virtual void OnExit() override final;
};

