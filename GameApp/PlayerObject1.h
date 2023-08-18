#pragma once

#include "../Engine/GameObject.h"

class TextureComponent;
class PlayerMovement;
class DirectionComponent;
class BoxCollider2D;

class PlayerObject1
	: public GameObject
{
private:
	TextureComponent* m_pTextureComponent = nullptr;
	PlayerMovement* m_pMovementComponent = nullptr;
	DirectionComponent* m_pDirectionComponent = nullptr;
	BoxCollider2D* m_pBoxCollider2D = nullptr;
	BoxCollider2D* m_pBoxCollider2DPart = nullptr;

public:
	~PlayerObject1() final;

public:
	bool Initialize() final;
	void Update(const float deltaTime) final;

	void OnCollisionEnter(Collider2D* otherCollision) override;
	void OnCollisionStay(Collider2D* otherCollision) override;
	void OnCollisionExit(Collider2D* otherCollision) override;

	void OnTriggerEnter(Collider2D* otherCollision) override;
	void OnTriggerStay(Collider2D* otherCollision) override;
	void OnTriggerExit(Collider2D* otherCollision) override;
};