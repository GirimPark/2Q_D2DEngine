#pragma once
#include "../Engine/GameObject.h"

enum class BTN_FUNC;
class BoxComponent;
class ButtonUI;
class PanelUI;

class UIObject :
    public GameObject
{
public:
    bool Initialize() final;
    void Update(const float deltaTime) final;

private:
    PanelUI* m_StartPanel = nullptr;
    ButtonUI* m_pStartButton = nullptr;
    ButtonUI* m_pMethodButton = nullptr;
    ButtonUI* m_pMadeByButton = nullptr;
    ButtonUI* m_pExitButton = nullptr;
};

