#include "framework.h"
#include "GameSettingWorld.h"

#include "GameSettingUIObject.h"

#include "../Engine/Event.h"
#include "../Engine/EventManager.h"
#include "../Engine/WorldManager.h"

bool GameSettingWorld::Initialize()
{
	m_pGameSettingUIObject = CreateGameObject<GameSettingUIObject>(L"MainUIObject", GROUP_TYPE::UI);

	bool res = __super::Initialize();
	assert(res);

	return true;
}

void GameSettingWorld::Finalize()
{
	World::Finalize();
}


void GameSettingWorld::Enter()
{
	std::cout << "GameSettingWorld Enter" << std::endl;

	EventManager::GetInstance()->RegisterListener(eEventType::ChangeWorldToInGame, dynamic_cast<EventListener*>(this));

	this->Initialize();
}

void GameSettingWorld::Exit()
{
	std::cout << "GameSettingWorld Exit" << std::endl;

	this->Finalize();
}

void GameSettingWorld::HandleEvent(Event* event)
{
	if (event->eventID == eEventType::ChangeWorldToInGame)
	{
		m_pWorldManager->ChangeWorld(WORLD_TYPE::INGAME);
	}
}