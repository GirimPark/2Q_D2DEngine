#include "framework.h"
#include "ChaeWorld.h"

#include "UIObject.h"

bool ChaeWorld::Initialize()
{
	m_pUIObject = CreateGameObject<UIObject>(L"FirstUI");

	bool res = __super::Initialize();
	assert(res);

	return true;
}