#pragma once
#include "struct.h"

/*---------------------------------------------------------------
AABB�� �ʿ��� ��� �ش� Ŭ������ �ν��Ͻ�ȭ �ؼ� ��������� ������.
Center�� Extend�� ������ ��踦 �����Ѵ�.
----------------------------------------------------------------*/
class AABB
{
public:
	framework::Vector2D m_Center;
	float m_Extend = 0.f;
	framework::Rect m_CullingBox;
	
	framework::Rect GetCullingBox();
	void CalCullingBox();
	bool CheckBRender(AABB& cameraAABB);
};
