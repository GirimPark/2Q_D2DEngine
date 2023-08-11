#include "pch.h"
#include "BoxCollider2D.h"

#include "CommonApp.h"

#include "CircleCollider2D.h"

bool BoxCollider2D::Initialize()
{
	const bool res = SceneComponent::Initialize();
	assert(res);

	return true;
}

void BoxCollider2D::Update(const float deltaTime)
{
	Collider2D::Update(deltaTime);
	m_collider.center = SceneComponent::GetWorldLocation();
}

void BoxCollider2D::Render(ID2D1RenderTarget* pRenderTarget)
{
	m_FinalTransform = m_WorldTransform * GetCameraTransform();
	pRenderTarget->SetTransform(m_FinalTransform);

	// �浹 ���ο� ���� �ݶ��̴� �ڽ� ��ȭ
	if (m_isCollision)
	{
		SetColor(D2D1::ColorF::Red);
		CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

		pRenderTarget->DrawRectangle(
			D2D1::RectF(-m_collider.extend.x, -m_collider.extend.x, m_collider.extend.x, m_collider.extend.y),
			CommonApp::m_pInstance->GetBrush(),
			5.0f
		);
	}
	else
	{
		SetColor(D2D1::ColorF::Green);
		CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

		pRenderTarget->DrawRectangle(
			D2D1::RectF(-m_collider.extend.x, -m_collider.extend.x, m_collider.extend.x, m_collider.extend.y),
			CommonApp::m_pInstance->GetBrush(),
			5.0f
		);
	}

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

bool BoxCollider2D::CheckIntersect(Collider2D* other) const
{
	// other�� BoxCollider2D�� ���
	const BoxCollider2D* temp1 = dynamic_cast<BoxCollider2D*>(other);
	if (temp1)
		return m_collider.Check_AABB_AABB(dynamic_cast<BoxCollider2D*>(other)->m_collider);

	// other�� CircleCollider2D�� ���
	const CircleCollider2D* temp2 = dynamic_cast<CircleCollider2D*>(other);
	if (temp2)
		return m_collider.Check_AABB_CC(dynamic_cast<CircleCollider2D*>(other)->m_collider);

	return false;
}

void BoxCollider2D::SetExtend(float x, float y)
{
	// �߽������� Ȯ��Ǵ� ����
	m_collider.extend.x = x;
	m_collider.extend.y = y;
}