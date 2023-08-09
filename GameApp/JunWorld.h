#pragma once

#include "../Engine/World.h"

class PlayerObject1;
class PlayerObject2;
class CameraObject;
class BoxObject;

class JunWorld
	: public World
{
public:
	bool Initialize() final;

private:
	PlayerObject1* m_pPlayerObject1 = nullptr;
	PlayerObject2* m_pPlayerObject2 = nullptr;

	//CameraObject* m_pCameraObject = nullptr;
	//BoxObject* m_pBitmapTestObject = nullptr;
};