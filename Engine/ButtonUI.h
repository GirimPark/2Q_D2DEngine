#pragma once
#include "UI.h"

enum  class BTN_FUNC
{
    NONE,
    CHANGE_SCENE,
    PAUSE_UI,
    DELTE_PARENT_UI,
};

class ButtonUI
    : public UI
{
public:
    void SetBtnFunction(BTN_FUNC _func);

    //void CheckMouseOn() override {};
    //void MouseLbtnDown() override {};
    //void MouseLbtnUp() override {};
    void MouseLbtnClicked() override;

public:
    bool Initialize() override final;
    void Update(const float deltaTime) override final;
    void Render(ID2D1RenderTarget* pRenderTarget) override final;

private:
    BTN_FUNC m_function = {};

};

