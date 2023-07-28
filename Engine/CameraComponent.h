#pragma once
#include "SceneComponent.h"
#include "AABB.h"

class CameraComponent
	: public SceneComponent
{
private:
    AABB m_ViewPort;

public:
    static D2D_MATRIX_3X2_F m_CameraTransform;

public:
    void SetExtend(float extend) { m_ViewPort.m_Extend = extend; }
    AABB GetViewPort() { return m_ViewPort; }

    void InvertCameraTransform() { D2D1InvertMatrix(&m_CameraTransform); }

    bool Initialize() override;
    void Update() override;

    friend class RenderComponent;
};

