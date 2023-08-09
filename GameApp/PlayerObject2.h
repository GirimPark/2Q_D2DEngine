#pragma once

#include "../Engine/GameObject.h"

class BoxComponent;
//class AnimationComponent;
class MovementComponent;
//class FSMComponent;
//class FSM;
class DirectionComponent;
class CircleCollider2D;

class PlayerObject2
	: public GameObject
{
private:
	BoxComponent* m_pBoxComponent = nullptr;
	//AnimationComponent* m_pAnimComponent = nullptr;
	MovementComponent* m_pMovementComponent = nullptr;
	//FSMComponent* m_pFSMComponent = nullptr;
	//FSM* m_pPlayerFSM = nullptr;
	DirectionComponent* m_pDirectionComponent = nullptr;
	CircleCollider2D* m_pCircleCollider2D = nullptr;

public:
	~PlayerObject2() override;

public:
	bool Initialize() override;
	void Update(const float deltaTime) override;
};