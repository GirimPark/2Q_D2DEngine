#pragma once

#include <vector>

class FSM;
class FSMTransition;

class FSMState
{
protected:
	FSM* m_pParentFSM = nullptr;

	std::wstring m_StateName;
	std::vector<FSMTransition*> m_Transitions;
	bool m_bFlip;	// 애니메이션 flip

public:
	virtual ~FSMState() { }

public:
	void SetParentFSM(FSM* parentFSM);

	void SetDefaultAnimationName();
	std::wstring GetName() const { return m_StateName; }
	void SetName(const std::wstring name) { m_StateName = name; }
	void AddTransition(FSMTransition* fsmStransiton) { m_Transitions.push_back(fsmStransiton); }

public:
	virtual bool CheckTransition();
	virtual void OnEnter() abstract;
	virtual void OnExit() abstract;
};

