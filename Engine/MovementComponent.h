#pragma once

#include "Component.h"

/// <summary>
/// �̵��� ���� ������Ʈ
/// MoveDirection�� LookDirection���� �̵��Ѵ�.
/// </summary>
class MovementComponent
	: public Component
{
private:
	float m_Speed = 1500.f;
	framework::Vector2D m_Velocity = { 0.f, 0.f };

private:
	int m_RawBX = 0;
	int m_RawBY = 0;

	framework::Vector2D m_ThumbLeft = { 0.f, 0.f };
	framework::Vector2D m_ThumbRight = { 0.f, 0.f };

	framework::Vector2D m_MoveDir = { 0.f, 0.f };
	framework::Vector2D m_LookDir = { 1.f, 0.f };

public:
	framework::Vector2D GetMoveDir() const { return m_MoveDir; }
	framework::Vector2D GetLookDir() const { return m_LookDir; }
	framework::Vector2D GetVelocity() const { return m_Velocity; }

	void XBOXController(int controllerIndex);

public:
	void Update(const float deltaTime) final;
};