#include "pch.h"
#include "DirectionComponent.h"

#include "CommonApp.h"
#include "GameObject.h"

#include "MovementComponent.h"

void DirectionComponent::Update(const float deltaTime)
{
	__super::Update(deltaTime);
}

void DirectionComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	m_FinalTransform = m_WorldTransform * GetCameraTransform();
	pRenderTarget->SetTransform(m_FinalTransform);

	SetColor(D2D1::ColorF::Yellow);
	CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

	// Draw Move Direction
	pRenderTarget->DrawLine(
		D2D1::Point2F(0.f, 0.f),
		D2D1::Point2F(
			50.f * dynamic_cast<MovementComponent*>(m_pOwner->GetComponent(L"MovementComponent"))->GetMoveDir().x,
			50.f * dynamic_cast<MovementComponent*>(m_pOwner->GetComponent(L"MovementComponent"))->GetMoveDir().y
		),
		CommonApp::m_pInstance->GetBrush(),
		3.f);

	SetColor(D2D1::ColorF::HotPink);
	CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

	// Draw Look Direction
	pRenderTarget->DrawLine(
		D2D1::Point2F(0.f, 0.f),
		D2D1::Point2F(
			50.f * dynamic_cast<MovementComponent*>(m_pOwner->GetComponent(L"MovementComponent"))->GetLookDir().x,
			50.f * dynamic_cast<MovementComponent*>(m_pOwner->GetComponent(L"MovementComponent"))->GetLookDir().y
		),
		CommonApp::m_pInstance->GetBrush(),
		3.f);

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}