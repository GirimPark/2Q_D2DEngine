#pragma once

#include "Component.h"

class FSM;
class AnimationComponent;

/*-------------------------------------------------
FSM�� ������Ʈ�� ���̱� ���� Component
FSM ������ ������ ����.
GameObject
-FSMComponent(!!)
 -FSM
  -FSMState
   -FSMTransition

EventManager �ٿ��� ���� ����
���� ���� �õ��ߴ� �Ŷ� ������ �ణ ������(23.08.03)
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

