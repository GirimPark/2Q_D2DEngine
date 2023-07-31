#pragma once
#include "struct.h"

/*---------------------------------------------------------------
AABB가 필요한 경우 해당 클래스를 인스턴스화 해서 멤버변수로 가진다.
Center와 Extend로 렌더링 경계를 결정한다.
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
