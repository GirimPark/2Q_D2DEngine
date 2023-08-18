#pragma once
#include "ItemObject.h"

class ShoeItem
	: public ItemObject
{
private:

public:
	bool Initialize() final;
	void Update(const float deltaTime) final;
};

