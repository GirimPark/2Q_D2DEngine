#pragma once

#include "../Engine/GameObject.h"

class BoxComponent;
class AnimationComponent;
class MovementComponent;
class FSMComponent;
class FSM;
class EventListener;
class DirectionComponent;

class PlayerObject
	: public GameObject
{
private:
	BoxComponent* m_pBoxComponent = nullptr;
	AnimationComponent* m_pAnimComponent = nullptr;
	MovementComponent* m_pMovementComponent = nullptr;
	FSMComponent* m_pFSMComponent = nullptr;
	FSM* m_pPlayerFSM = nullptr;
	DirectionComponent* m_pDirectionComponent = nullptr;

public:
	~PlayerObject() override;

public:
	bool Initialize() override;
	void Update(const float deltaTime) override;
};