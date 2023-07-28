#pragma once
#include "SceneComponent.h"
#include "CameraComponent.h"
#include "AABB.h"

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

	AABB m_ComponentAABB;

public:
	const AABB* GetComponentAABB() const { return &m_ComponentAABB; }

	const D2D_MATRIX_3X2_F GetCameraTransform() { return CameraComponent::m_CameraTransform; }

public:
	virtual bool Initialize() override abstract;	// 컬링박스 범위 설정
	virtual void Render(ID2D1RenderTarget* pRenderTarget) abstract;
	virtual void CalAABB() abstract;
};

