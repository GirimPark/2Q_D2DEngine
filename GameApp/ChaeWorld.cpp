#include "framework.h"
#include "ChaeWorld.h"

#include "DemoObject.h"
#include "PlayerObject1.h"
#include "CameraObject.h"
#include "UIObject.h"

#include "../Engine/CommonApp.h"

bool ChaeWorld::Initialize()
{
	m_pUIObject = CreateGameObject<UIObject>(L"FirstUI");

	bool res = __super::Initialize();
	assert(res);

	return true;
}