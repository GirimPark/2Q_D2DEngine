#pragma once

#include "SceneComponent.h"
#include "CameraComponent.h"

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

public:
	const D2D_MATRIX_3X2_F GetCameraTransform() const { return CameraComponent::m_CameraTransform; }

public:
	virtual void Render(ID2D1RenderTarget* pRenderTarget) abstract;
};

