#include "pch.h"
#include "BoxCollider2D.h"

#include "CommonApp.h"
#include "GameObject.h"

#include "CircleCollider2D.h"

bool BoxCollider2D::Initialize()
{
	bool res = SceneComponent::Initialize();
	assert(res);

	return true;
}

void BoxCollider2D::Update(const float deltaTime)
{
	__super::Update(deltaTime);
}

void BoxCollider2D::Render(ID2D1RenderTarget* pRenderTarget)
{
	m_FinalTransform = m_WorldTransform * GetCameraTransform();
	pRenderTarget->SetTransform(m_FinalTransform);

	CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

	pRenderTarget->DrawRectangle(
		D2D1::RectF(-100.f, -100.f, 100.f, 100.f),
		CommonApp::m_pInstance->GetBrush(),
		5.f
	);

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

bool BoxCollider2D::CheckIntersect(Collider2D* other) const
{
	// other가 BoxCollider2D인 경우
	BoxCollider2D* temp1 = dynamic_cast<BoxCollider2D*>(other);
	if (temp1)
		return m_collider.Check_AABB_AABB(dynamic_cast<BoxCollider2D*>(other)->m_collider);

	// other가 CircleCollider2D인 경우
	CircleCollider2D* temp2 = dynamic_cast<CircleCollider2D*>(other);
	if (temp2)
		return m_collider.Check_AABB_CC(dynamic_cast<CircleCollider2D*>(other)->m_collider);

	return false;
}

void BoxCollider2D::SetExtend(float x, float y)
{
	// 중심점에서 확장되는 길이
	m_collider.extend.x = x;
	m_collider.extend.y = y;
}