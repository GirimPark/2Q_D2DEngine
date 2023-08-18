#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// 메인 화면의 UIObject
/// </summary>

class TextureComponent;
class ButtonUI;
class PanelUI;

class MainUIObject :
    public GameObject
{
public:
    bool Initialize() final;
    void Update(const float deltaTime) final;

private:
    // 텍스처
    // 활성화
    TextureComponent* m_pGameStartTexture = nullptr;
    TextureComponent* m_pInstructionTexture = nullptr;
    TextureComponent* m_pMadeByTexture = nullptr;
    TextureComponent* m_pExitTexture = nullptr;
    TextureComponent* m_pOkayTexture = nullptr;
    TextureComponent* m_pCancelTexture = nullptr;

    // 비활성화


    // 버튼
    // 활성화
    PanelUI* m_pMainWorldPanel = nullptr;
    ButtonUI* m_pStartButton = nullptr;
    ButtonUI* m_pInstructionButton = nullptr;
    ButtonUI* m_pMadeByButton = nullptr;
    ButtonUI* m_pExitButton = nullptr;
    ButtonUI* m_pOkayButton = nullptr;
    ButtonUI* m_pCancelButton = nullptr;

    // 비활성화
};