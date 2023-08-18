#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// 
/// </summary>

class TextureComponent;
class ButtonUI;
class PanelUI;

class InstructionUIObject :
    public GameObject
{
private:
    TextureComponent* m_pPrevTexture = nullptr;

    PanelUI* m_pInstructionWorldPanel = nullptr;
    PanelUI* m_pShowPanel = nullptr;

    ButtonUI* m_pInstructionButton = nullptr;
    ButtonUI* m_pControllerButton = nullptr;
    ButtonUI* m_pKeyBoardButton = nullptr;
    ButtonUI* m_pPrevButton = nullptr;
    ButtonUI* m_pOkayButton = nullptr;
    ButtonUI* m_pCancelButton = nullptr;

public:
    bool Initialize() final;
    void Update(const float deltaTime) final;
};

