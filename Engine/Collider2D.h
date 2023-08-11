#pragma once

#include "RenderComponent.h"

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
	bool m_isCollision = false;

public:
	void SetWidth(const float width) { m_Width = width; }
	void SetHeight(const float height) { m_Height = height; }
	void SetColor(D2D1::ColorF color) { m_Color = color; }

public:
	bool Initialize() override;
	void Update(const float deltaTime) override;
	void Render(ID2D1RenderTarget* pRenderTarget) override;

public:
	virtual bool CheckIntersect(Collider2D* other) const abstract;
	void ProcessBlock(float deltaTime) const;
};