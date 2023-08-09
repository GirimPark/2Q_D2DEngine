#pragma once

#include "../Engine/World.h"

class DemoObject;
class PlayerObject;
class CameraObject;

class TestWorld
	: public World
{
private:
	DemoObject* m_pDemoObject = nullptr;
	PlayerObject* m_pPlayerObject = nullptr;
	CameraObject* m_pCameraObject = nullptr;

public:
	bool Initialize() final;
};