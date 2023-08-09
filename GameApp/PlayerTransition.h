#pragma once

#include "../Engine/FSMTransition.h"
#include "../Engine/EventListener.h"

class PlayerTransition
	: public FSMTransition
	, public EventListener
{
protected:
	bool m_bMoving = false;
	framework::Vector2D m_LookDirection = { 0.f, 0.f };

public :
	std::pair<std::wstring, bool> operator()() override abstract;
	void HandleEvent(Event* event) final;
};

class IdleToMove : public PlayerTransition
{
public:
	virtual std::pair<std::wstring, bool> operator()() override
	{
		if(m_bMoving)
		{
			if (m_LookDirection.x >= 0)
				return { L"MOVE", false };
			else
				return { L"MOVE", true };
		}
		else
		{
			if (m_LookDirection.x >= 0)
				return { L"IDLE", false };
			else
				return { L"IDLE", true };
		}
	}
};

class MoveToIdle : public PlayerTransition
{
public:
	virtual std::pair<std::wstring, bool> operator()() override
	{
		if(!m_bMoving)
		{
			if(m_LookDirection.x >= 0)
				return { L"IDLE", false };
			else
				return { L"IDLE", true };
		}
		else
		{
			if (m_LookDirection.x >= 0)
				return { L"MOVE", false };
			else
				return { L"MOVE", true };
		}
	}
};