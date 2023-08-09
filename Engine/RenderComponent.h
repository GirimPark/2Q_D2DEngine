#pragma once

#include "SceneComponent.h"
#include "CameraComponent.h"

/*------------------------------------------------------
렌더링이 필요한 컴포넌트는 해당 클래스를 상속받아 구현한다.
인스턴스화하지 않는다.
-------------------------------------------------------*/
class RenderComponent
	: public SceneComponent
{
protected:
	int m_RenderOrder = 0;
	bool m_bVisible = true;

public:
	const D2D_MATRIX_3X2_F GetCameraTransform() const { return CameraComponent::m_CameraTransform; }

public:
	virtual void Render(ID2D1RenderTarget* pRenderTarget) abstract;
};

