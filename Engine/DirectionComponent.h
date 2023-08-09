#pragma once

#include "RenderComponent.h"

/// <summary>
/// 물체의 이동 방향 및 바라보는 방향을 표시하는 컴포넌트
/// </summary>
class DirectionComponent :
    public RenderComponent
{
private:
	float m_Width = 0.f;
	float m_Height = 0.f;
	D2D1::ColorF m_Color = D2D1::ColorF::Yellow;

public:
	void SetWidth(const float width) { m_Width = width; }
	void SetHeight(const float height) { m_Height = height; }
	void SetColor(D2D1::ColorF color) { m_Color = color; }

public:
	void Update(const float deltaTime) final;
	void Render(ID2D1RenderTarget* pRenderTarget) final;
};