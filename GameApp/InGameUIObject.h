#pragma once
#include "../Engine/GameObject.h"

class TextureComponent;
class ButtonUI;
class PanelUI;

class InGameUIObject :
    public GameObject
{
private:
    TextureComponent* m_pItemTexture1 = nullptr;
    TextureComponent* m_pItemTexture2 = nullptr;
    TextureComponent* m_pItemTexture3 = nullptr;
    TextureComponent* m_pItemTexture4 = nullptr;
    TextureComponent* m_pBackGround = nullptr;

    PanelUI* m_pInGamePanel = nullptr;

    PanelUI* m_pGoalMoneyPanel = nullptr;

    PanelUI* m_Player1Item = nullptr;
    //PanelUI* m_Player1Item2 = nullptr;
    //PanelUI* m_Player1Item3 = nullptr;

    PanelUI* m_Player2Item = nullptr;
    //PanelUI* m_Player2Item2 = nullptr;
    //PanelUI* m_Player2Item3 = nullptr;

    PanelUI* m_Player3Item = nullptr;
    //PanelUI* m_Player3Item2 = nullptr;
    //PanelUI* m_Player3Item3 = nullptr;

    PanelUI* m_Player4Item = nullptr;
    //PanelUI* m_Player4Item2 = nullptr;
    //PanelUI* m_Player4Item3 = nullptr;

public:
    bool Initialize() final;
    void Update(const float deltaTime) final;
};
