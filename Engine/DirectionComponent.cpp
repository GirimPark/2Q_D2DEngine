#include "pch.h"
#include "DirectionComponent.h"

#include "CommonApp.h"
#include "GameObject.h"
#include "MovementComponent.h"

void DirectionComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	m_FinalTransform = m_WorldTransform * GetCameraTransform();
	pRenderTarget->SetTransform(m_FinalTransform);

	SetColor(D2D1::ColorF::Yellow);
	CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

	const framework::Vector2D moveDir = dynamic_cast<MovementComponent*>(m_pOwner->GetComponent(L"MovementComponent"))->GetMoveDir();
	const framework::Vector2D lookDir = dynamic_cast<MovementComponent*>(m_pOwner->GetComponent(L"MovementComponent"))->GetLookDir();
	const framework::Vector2D velocity = dynamic_cast<MovementComponent*>(m_pOwner->GetComponent(L"MovementComponent"))->GetVelocity();

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

	// std::cout << moveDir.x << " " << moveDir.y << std::endl;
	// std::cout << lookDir.x << " " << lookDir.y << std::endl;
	// std::cout << velocity.x << " " << velocity.y << std::endl;

	// std::cout << SceneComponent::GetRelativeLocation().x << " " << SceneComponent::GetRelativeLocation().y << std::endl;

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}