#include "framework.h"
#include "JunWorld.h"

#include "PlayerObject1.h"
#include "PlayerObject2.h"

bool JunWorld::Initialize()
{
	m_pPlayerObject1 = CreateGameObject<PlayerObject1>(L"PlayerObject1");
	m_pPlayerObject2 = CreateGameObject<PlayerObject2>(L"PlayerObject2");
	// m_pBitmapTestObject = CreateGameObject<BoxObject>(L"BitmapTestObject");

	// m_pCameraObject = CreateGameObject<CameraObject>(L"CameraObject");
	// m_pCameraObject->SetOwnerObj(m_pPlayerObject1);

	const bool res = World::Initialize();
	assert(res);

	return true;
}