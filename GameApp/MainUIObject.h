#pragma once
#include "../Engine/GameObject.h"

/// <summary>
/// ���� ȭ���� UIObject
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
    // �ؽ�ó
    // Ȱ��ȭ
    TextureComponent* m_pGameStartTexture = nullptr;
    TextureComponent* m_pInstructionTexture = nullptr;
    TextureComponent* m_pMadeByTexture = nullptr;
    TextureComponent* m_pExitTexture = nullptr;
    TextureComponent* m_pOkayTexture = nullptr;
    TextureComponent* m_pCancelTexture = nullptr;

    // ��Ȱ��ȭ


    // ��ư
    // Ȱ��ȭ
    PanelUI* m_pMainWorldPanel = nullptr;
    ButtonUI* m_pStartButton = nullptr;
    ButtonUI* m_pInstructionButton = nullptr;
    ButtonUI* m_pMadeByButton = nullptr;
    ButtonUI* m_pExitButton = nullptr;
    ButtonUI* m_pOkayButton = nullptr;
    ButtonUI* m_pCancelButton = nullptr;

    // ��Ȱ��ȭ
};