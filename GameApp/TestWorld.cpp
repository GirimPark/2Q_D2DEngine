#include "framework.h"
#include "TestWorld.h"

#include "DemoObject.h"
#include "PlayerObject.h"

bool TestWorld::Initialize()
{
	m_pDemoObject = CreateGameObject<DemoObject>(L"SolarSystem");
	m_pPlayerObject = CreateGameObject<PlayerObject>(L"PlayerObject1");
	//m_pCameraObject = CreateGameObject<CameraObject>(L"CameraObject");
	//m_pCameraObject->SetOwnerObj(m_pPlayerObject);

	bool res = __super::Initialize();
	assert(res);

	return true;
}