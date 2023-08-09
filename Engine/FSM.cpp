#include "pch.h"
#include "FSM.h"

#include "AnimationComponent.h"
#include "FSMComponent.h"
#include "FSMState.h"

void FSM::AddState(const std::wstring name, FSMState* state)
{
	m_States.insert(std::pair<std::wstring, FSMState*>(name, state));
	state->SetName(name);
	state->SetParentFSM(this);
}

void FSM::SetDefaultState(FSMState* defaultState)
{
	m_pCurState = defaultState;
}

void FSM::Update(const float deltaTime)
{
	// 현재 애니메이션이 종료되는지, 현재 상태에 달린 Transition들을 체크
	if (m_bAnimEnd && m_pCurState->CheckTransition())
	{
		// 현재 애니메이션 재생이 끝났다면
		m_bAnimEnd = false;

		m_pCurState = m_pNextState;
		m_pCurState->OnEnter();
	}
}
