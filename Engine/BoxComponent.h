#pragma once
#include "RenderComponent.h"

/// <summary>
///	¹Ú½º ÇÏ³ª ¶î·Õ ±×¸®±â
/// </summary>
class BoxComponent
	: public RenderComponent
{
private:
	float m_Width = 0.f;
	float m_Height = 0.f;
	D2D1::ColorF m_Color = D2D1::ColorF::Black;

public:
	void SetWidth(const float width) { m_Width = width; }
	void SetHeight(const float height) { m_Height = height; }
	float GetWidth() const { return m_Width; }
	float GetHeight()const { return m_Height; }

	void SetColor(D2D1::ColorF color) { m_Color = color; }

public:
	void Render(ID2D1RenderTarget* pRenderTarget) final; 
};