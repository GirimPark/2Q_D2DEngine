#pragma once

#include "Collider2D.h"

class BoxCollider2D :
    public Collider2D
{
public:
	bool Initialize() final;
	void Update(const float deltaTime) final;
	void Render(ID2D1RenderTarget* pRenderTarget) final;

public:
	bool CheckIntersect(Collider2D* other) const final;

public:
	void SetExtend(float x, float y);

public:
	MYAABB m_collider;
};