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
	// ���� �ִϸ��̼��� ����Ǵ���, ���� ���¿� �޸� Transition���� üũ
	if (m_bAnimEnd && m_pCurState->CheckTransition())
	{
		// ���� �ִϸ��̼� ����� �����ٸ�
		m_bAnimEnd = false;

		m_pCurState = m_pNextState;
		m_pCurState->OnEnter();
	}
}
