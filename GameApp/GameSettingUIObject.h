#pragma once
#include "../Engine/GameObject.h"

class TextureComponent;
class ButtonUI;
class PanelUI;

class GameSettingUIObject :
    public GameObject
{
private:
    TextureComponent* m_pStartTexture = nullptr;
    TextureComponent* m_pOkayTexture = nullptr;
    TextureComponent* m_pCancelTexture = nullptr;
    TextureComponent* m_pLeftTexture = nullptr;
    TextureComponent* m_pRightTexture = nullptr;

    PanelUI* m_pGameSettingPanel = nullptr;

    ButtonUI* m_pSelectMap1 = nullptr;
    ButtonUI* m_pSelectMap2 = nullptr;
    ButtonUI* m_pSelectMap3 = nullptr;

    PanelUI* m_pMapImage = nullptr;

    ButtonUI* m_pLeftButton = nullptr;
    ButtonUI* m_pRightButton = nullptr;

    ButtonUI* m_pItemButton1 = nullptr;
    ButtonUI* m_pItemButton2 = nullptr;
    ButtonUI* m_pItemButton3 = nullptr;
    ButtonUI* m_pItemButton4 = nullptr;
    ButtonUI* m_pItemButton5 = nullptr;
    ButtonUI* m_pItemButton6 = nullptr;
    ButtonUI* m_pItemButton7 = nullptr;
    ButtonUI* m_pItemButton8 = nullptr;
    ButtonUI* m_pItemButton9 = nullptr;
    ButtonUI* m_pItemButton10 = nullptr;
    ButtonUI* m_pItemButton11 = nullptr;
    ButtonUI* m_pItemButton12 = nullptr;

    ButtonUI* m_pStartButton = nullptr;

    ButtonUI* m_pOkayButton = nullptr;
    ButtonUI* m_pCancelButton = nullptr;

public:
    bool Initialize() final;
    void Update(const float deltaTime) final;
};