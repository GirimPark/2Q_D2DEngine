#include "pch.h"
#include "BoxComponent.h"

#include "CommonApp.h"

void BoxComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

	m_FinalTransform = m_WorldTransform * GetCameraTransform();
	pRenderTarget->SetTransform(m_FinalTransform);

	pRenderTarget->DrawRectangle(
		D2D1::RectF(-m_Width / 2, -m_Height / 2, m_Width / 2, m_Height / 2),
		CommonApp::m_pInstance->GetBrush(),
		2.f);

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}