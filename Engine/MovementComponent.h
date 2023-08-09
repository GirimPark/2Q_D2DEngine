#pragma once

#include "Component.h"

/*------------------------------------------------
이동을 위한 컴포넌트
물리 파트 적용 전 임시로 사용(23.08.02)
-------------------------------------------------*/
class MovementComponent
	: public Component
{
private:
	bool m_bMoving = false;
	float m_Velocity = 400.f;

	framework::Vector2D m_MoveDir = { 0.f, 0.f };
	framework::Vector2D m_LookDir = { 1.f, 0.f };

public:
	framework::Vector2D GetMoveDir() const { return m_MoveDir; }
	framework::Vector2D GetLookDir() const { return m_LookDir; }

	void XBOXController(int controllerIndex);

public:
	void Update(const float deltaTime) final;
};