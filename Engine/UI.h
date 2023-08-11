#pragma once
#include "RenderComponent.h"

class UI :
    public RenderComponent
{
public:
    bool Initialize() override;
    void Update(const float deltaTime) override;
    void Render(ID2D1RenderTarget* pRenderTarget) override;

public:
    framework::Vector2D  GetFinalPos() { return m_finalUIPos; }

    // UI�� ���� setting
    void SetColor(D2D1::ColorF color) { m_Color = color; }

    void FocusOn(D2D1::ColorF changeColor)
	{
    	m_changeColor = m_Color; m_Color = changeColor;
    }
    void FocusOut() { m_Color = m_changeColor; }

    void SetWidth(const float width) { m_Width = width; }
    float GetWidth() const { return m_Width; }

    void SetHeight(const float height) { m_Height = height; }
    float GetHeight()const { return m_Height; }

    bool IsLbtnDown() const { return m_bLbtnDown; }
    bool IsMouseOn() const { return m_bMouseOn; }

    void SetLbtnDown(bool isDown) { m_bLbtnDown = isDown; }
    void SetMouseOn(bool isOn) { m_bMouseOn = isOn; }

    void SetYIndex(size_t y) { m_yIndex = y; }
    size_t GetYIndex() const { return m_yIndex; }

    void SetXIndex(size_t x) { m_xIndex = x; }
    size_t GetXIndex() const { return m_xIndex; }

public:
    // ���콺�� UI�� ���� ��
    virtual void CheckMouseOn();
    virtual void MouseLbtnDown() {};
    virtual void MouseLbtnUp() {};
    virtual void MouseLbtnClicked() {};

private:
    D2D1::ColorF m_changeColor = D2D1::ColorF::Black;

protected:
	framework::Vector2D m_finalUIPos = {0,0};

    float m_Width = 0.f;
    float m_Height = 0.f;
    D2D1::ColorF m_Color = D2D1::ColorF::Black;

    bool m_bLbtnDown = false;
    bool m_bMouseOn = false;

    size_t m_xIndex = 0;
    size_t m_yIndex = 0;
};