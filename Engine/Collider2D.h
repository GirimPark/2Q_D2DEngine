#pragma once

#include "RenderComponent.h"

#include "GameObject.h"

class MYAABB;
class MYCC;

/// <summary>
/// AABB 충돌 클래스
/// </summary>
class MYAABB
{
public:
	framework::Vector2D center;
	framework::Vector2D extend;

public:
	bool Check_AABB_AABB(const MYAABB& other) const;

	// MYAABB - MYCC Collision
	bool Check_AABB_CC(const MYCC& other) const;
};

/// <summary>
/// Circle 충돌 클래스
/// </summary>
class MYCC
{
public:
	framework::Vector2D center;
	float radius;

public:
	bool Check_CC_CC(const MYCC& other) const;

	// MYCC - MYAABB Collision
	bool Check_CC_AABB(const MYAABB& other) const;
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
	void SetWidth(const float width) { m_Width = width; }
	void SetHeight(const float height) { m_Height = height; }
	void SetColor(D2D1::ColorF color) { m_Color = color; }

public:
	bool Initialize() override;
	void Update(const float deltaTime) override;
	void Render(ID2D1RenderTarget* pRenderTarget) override;

public:
	virtual bool CheckIntersect(Collider2D* other) const abstract;

public:
	void ProcessBlock(float deltaTime)
	{
		// deltaTime 만큼 다시 뒤로 돌려보낸다
		m_pOwner->GetRootComponent()->AddRelativeLocation(80.f * deltaTime * -1);
		// m_pTransform->Move(m_pTransform->GetVelocity() * deltaTime * -1);
	}

public:
	bool m_isCollision;		// 충돌 여부
};