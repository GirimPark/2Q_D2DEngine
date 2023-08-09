#pragma once

#include "../Engine/World.h"

class UIObject;

class ChaeWorld
	: public World
{
public:
	bool Initialize() final;
};
