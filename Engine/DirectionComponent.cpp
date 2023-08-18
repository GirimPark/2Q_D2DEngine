#include "pch.h"
#include "DirectionComponent.h"

#include "CommonApp.h"
#include "GameObject.h"
#include "PlayerMovement.h"

void DirectionComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	m_FinalTransform = m_WorldTransform * GetCameraTransform();
	pRenderTarget->SetTransform(m_FinalTransform);

	const framework::Vector2D moveDir = dynamic_cast<PlayerMovement*>(m_pOwner->GetComponent(L"PlayerMovement"))->GetMoveDir();
	const framework::Vector2D lookDir = dynamic_cast<PlayerMovement*>(m_pOwner->GetComponent(L"PlayerMovement"))->GetLookDir();
	const framework::Vector2D velocity = dynamic_cast<PlayerMovement*>(m_pOwner->GetComponent(L"PlayerMovement"))->GetVelocity();

	SetColor(D2D1::ColorF::Yellow);
	CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

	// Draw Move Direction
	pRenderTarget->DrawLine(
		D2D1::Point2F(0.f, 0.f),
		D2D1::Point2F(
			50.f * moveDir.x,
			50.f * moveDir.y
		),
		CommonApp::m_pInstance->GetBrush(),
		3.f);

	SetColor(D2D1::ColorF::HotPink);
	CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

	// Draw Look Direction
	pRenderTarget->DrawLine(
		D2D1::Point2F(0.f, 0.f),
		D2D1::Point2F(
			50.f * lookDir.x,
			50.f * lookDir.y
		),
		CommonApp::m_pInstance->GetBrush(),
		3.f);

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}