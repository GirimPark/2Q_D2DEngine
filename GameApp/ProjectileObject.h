#pragma once

#include "ItemObject.h"

class BoxComponent;
class BoxCollider2D;

class ProjectileObject :
    public ItemObject
{
private:
	BoxComponent* m_pBoxComponent = nullptr;
	BoxCollider2D* m_pBoxCollider2D = nullptr;

private:
	float m_Speed = 600.f;

	framework::Vector2D m_Position = { 0.f, 0.f };
	framework::Vector2D m_Direction = { 1.0f, 0.f };
	framework::Vector2D m_Velocity = { 1.0f, 0.f };

private:
	float m_LifeTime = 0.f;
	float m_MaxLifeTime = 2.f;

public:
	~ProjectileObject() final;

public:
	bool Initialize() final;
	void Update(float deltaTime) final;

	void OnCollisionEnter(Collider2D* otherCollision) final;
	void OnCollisionStay(Collider2D* otherCollision) final;
	void OnCollisionExit(Collider2D* otherCollision) final;

	void OnTriggerEnter(Collider2D* otherCollision) final;
	void OnTriggerStay(Collider2D* otherCollision) final;
	void OnTriggerExit(Collider2D* otherCollision) final;

public:
	void SetSpeed(const float speed) { m_Speed = speed; }
	void SetPosition(const framework::Vector2D& position) { m_Position = position; }
	void SetPosition(float x, float y) { m_Position = { x,y }; }
	void SetDirection(const framework::Vector2D& direction) { m_Direction = direction; }

	float GetSpeed() const { return m_Speed; }
	framework::Vector2D GetDirection() const { return m_Direction; }
};