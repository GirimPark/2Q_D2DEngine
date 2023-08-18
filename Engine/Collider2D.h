#pragma once

#include "RenderComponent.h"

enum class COLLISION_TPYE
{
	COLLISION = 0,
	TRIGGER,
	NONE,

	END
};

struct AABB;
struct CC;

/// <summary>
/// AABB �浹
/// </summary>
struct AABB
{
	framework::Vector2D center;	// �߽���
	framework::Vector2D extend; // Ȯ�� ����

	// AABB - AABB Collision
	bool Check_AABB_AABB(const AABB& other) const;
	// AABB - CC Collision
	bool Check_AABB_CC(const CC& other) const;
};

/// <summary>
/// Circle �浹
/// </summary>
struct CC
{
	framework::Vector2D center;	// �߽���
	float radius;				// ������

	// CC - CC Collision
	bool Check_CC_CC(const CC& other) const;
	// CC - AABB Collision
	bool Check_CC_AABB(const AABB& other) const;
};

/// <summary>
/// ��ü�� �浹�� ����ϴ� ������Ʈ�� ��� Ŭ����
/// </summary>
class Collider2D :
    public RenderComponent
{
protected:
	float m_Width = 0.f;
	float m_Height = 0.f;
	D2D1::ColorF m_Color = D2D1::ColorF::Green;

public:
	COLLISION_TPYE m_CollisionType = COLLISION_TPYE::COLLISION;
	bool m_IsCollision = false;
	bool m_IsTrigger = false;

	static UINT m_NextID;			// ���� Collider2D�� ID
	UINT m_CollisionCount = 0;		// �浹���� �ٸ� �浹ü ����
	UINT m_ID = 0;					// Collider2D�� ID

public:
	Collider2D();
	~Collider2D() override;

public:
	void SetWidth(const float width) { m_Width = width; }
	void SetHeight(const float height) { m_Height = height; }
	void SetColor(D2D1::ColorF color) { m_Color = color; }

public:
	COLLISION_TPYE GetCollisionType() const { return m_CollisionType; }
	void SetCollisionType(COLLISION_TPYE type) { m_CollisionType = type; }

	void TurnOn_IsCollision(Collider2D* otherCollision) { m_IsCollision = true; otherCollision->m_IsCollision = true; }
	void TurnOff_IsCollision(Collider2D* otherCollision) { m_IsCollision = false; otherCollision->m_IsCollision = false; }

	void TurnOn_IsTrigger(Collider2D* otherCollision) { m_IsTrigger = true; otherCollision->m_IsTrigger = true; }
	void TurnOff_IsTrigger(Collider2D* otherCollision) { m_IsTrigger = false; otherCollision->m_IsTrigger = false; }
public:
	bool Initialize() override;
	void Update(const float deltaTime) override;
	void Render(ID2D1RenderTarget* pRenderTarget) override;

public:
	virtual bool CheckIntersect(Collider2D* other) const abstract;

public:
	UINT GetID() const { return m_ID; }

public:
	virtual void OnCollisionEnter(Collider2D* otherCollision) abstract;
	virtual void OnCollisionStay(Collider2D* otherCollision) abstract;
	virtual void OnCollisionExit(Collider2D* otherCollision) abstract;

	virtual void OnTriggerEnter(Collider2D* otherCollision) abstract;
	virtual void OnTriggerStay(Collider2D* otherCollision) abstract;
	virtual void OnTriggerExit(Collider2D* otherCollision) abstract;

public:
	virtual void ProcessBlock(Collider2D* otherCollision) abstract;
};