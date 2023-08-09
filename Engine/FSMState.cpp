#include "pch.h"
#include "FSMState.h"

#include "AnimationComponent.h"
#include "EventManager.h"
#include "FSMComponent.h"
#include "FSM.h"
#include "FSMTransition.h"

void FSMState::SetParentFSM(FSM* parentFSM)
{
	m_pParentFSM = parentFSM;
}

void FSMState::SetDefaultAnimationName()
{
	framework::EVENT_ANIMATION_INFO animationInfo = { m_StateName, false };
	EventManager::GetInstance()->SendEvent(eEventType::SetDefaultAnimation, animationInfo);
}

bool FSMState::CheckTransition()
{
	for (auto transition : m_Transitions)
	{
		std::wstring nextStateName = (*transition)().first;
		m_bFlip = (*transition)().second;
		if (!nextStateName.empty())
		{
			// state 목록에서 find
			FSMState* nextState = m_pParentFSM->FindState(nextStateName);
			m_pParentFSM->SetNextState(nextState);
			return true;
		}
	}

	return false;
}
