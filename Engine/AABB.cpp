#include "pch.h"
#include "AABB.h"

framework::Rect AABB::GetCullingBox()
{
	return m_CullingBox;
}
void AABB::CalCullingBox()
{
	m_CullingBox = { m_Center.x - m_Extend, m_Center.y - m_Extend, m_Center.x + m_Extend, m_Center.y + m_Extend };
}

bool AABB::CheckBRender(AABB& cameraAABB)
{
	if (m_CullingBox.right >= cameraAABB.m_CullingBox.left && m_CullingBox.left <= cameraAABB.m_CullingBox.right
		&& m_CullingBox.bottom >= cameraAABB.m_CullingBox.top && m_CullingBox.top <= cameraAABB.m_CullingBox.bottom)
		return true;
	else
		return false;
}