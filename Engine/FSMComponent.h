#pragma once

#include "Component.h"

class FSM;
class AnimationComponent;

/*-------------------------------------------------
FSM을 오브젝트에 붙이기 위한 Component
FSM 구조는 다음과 같다.
GameObject
-FSMComponent(!!)
 -FSM
  -FSMState
   -FSMTransition

EventManager 붙여서 변경 예정
구조 변경 시도했던 거랑 섞여서 약간 더러움(23.08.03)
--------------------------------------------------*/
class FSMComponent
	: public Component
{
private:
	FSM* m_FSM = nullptr;

public:
    void AttachFSM(FSM* _FSM, AnimationComponent* AnimComponent);

public:
    virtual void Update(const float deltaTime) override final;
};

