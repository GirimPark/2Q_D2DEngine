#pragma once
#include "SceneComponent.h"
#include "CameraComponent.h"
#include "AABB.h"

/*------------------------------------------------------
�������� �ʿ��� ������Ʈ�� �ش� Ŭ������ ��ӹ޾� �����Ѵ�.
�ν��Ͻ�ȭ���� �ʴ´�.
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
	virtual bool Initialize() override abstract;	// �ø��ڽ� ���� ����
	virtual void Render(ID2D1RenderTarget* pRenderTarget) abstract;
	virtual void CalAABB() abstract;
};

