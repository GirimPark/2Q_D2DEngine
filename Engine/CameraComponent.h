#pragma once

#include "SceneComponent.h"

/*------------------------------------------------------------------------------------
카메라 컴포넌트. 카메라 오브젝트가 존재함을 전제로 작성했다.
(컴포넌트만을 붙여서 동작하는지는 확인 필요)
LateUpdate에 카메라 트랜스폼의 역행렬을 한 번 구한다.
단 하나 존재하는 카메라 트랜스폼을 RenderComponent에서 쓰기 위해 friend Class로 선언한다.
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

