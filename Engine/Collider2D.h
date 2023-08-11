#pragma once

#include "RenderComponent.h"

struct AABB;
struct CC;

/// <summary>
/// AABB 충돌
/// </summary>
struct AABB
{
	framework::Vector2D center;	// 중심점
	framework::Vector2D extend; // 확장 범위

	// AABB - AABB Collision
	bool Check_AABB_AABB(const AABB& other) const;
	// AABB - CC Collision
	bool Check_AABB_CC(const CC& other) const;
};

/// <summary>
/// Circle 충돌
/// </summary>
struct CC
{
	framework::Vector2D center;	// 중심점
	float radius;				// 반지름

	// CC - CC Collision
	bool Check_CC_CC(const CC& other) const;
	// CC - AABB Collision
	bool Check_CC_AABB(const AABB& other) const;
};

/// <summary>
/// 물체의 충돌을 담당하는 컴포넌트의 기반 클래스
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