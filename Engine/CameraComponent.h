#pragma once

#include "SceneComponent.h"

/*------------------------------------------------------------------------------------
ī�޶� ������Ʈ. ī�޶� ������Ʈ�� �������� ������ �ۼ��ߴ�.
(������Ʈ���� �ٿ��� �����ϴ����� Ȯ�� �ʿ�)
LateUpdate�� ī�޶� Ʈ�������� ������� �� �� ���Ѵ�.
�� �ϳ� �����ϴ� ī�޶� Ʈ�������� RenderComponent���� ���� ���� friend Class�� �����Ѵ�.
--------------------------------------------------------------------------------------*/
class CameraComponent
	: public SceneComponent
{
public:
    static D2D_MATRIX_3X2_F m_CameraTransform;

public:
    void InvertCameraTransform() { D2D1InvertMatrix(&m_CameraTransform); }

    bool Initialize() override;
    void Update(const float deltaTime) override;

    friend class RenderComponent;
};

