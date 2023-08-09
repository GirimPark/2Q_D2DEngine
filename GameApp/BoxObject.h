#pragma once

#include "../Engine/GameObject.h"

class BoxComponent;

class BoxObject :
    public GameObject
{
private:
	BoxComponent* m_pBoxComponent = nullptr;
public:
	bool Initialize() final;
	void Update(const float deltaTime) final;
};