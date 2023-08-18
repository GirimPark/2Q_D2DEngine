#include "framework.h"
#include "InstructionWorld.h"

#include "InstructionUIObject.h"

#include "../Engine/Event.h"
#include "../Engine/EventManager.h"
#include "../Engine/WorldManager.h"

bool InstructionWorld::Initialize()
{
	m_pInstructionUIObject = CreateGameObject<InstructionUIObject>
	(L"InstructionUIObject", GROUP_TYPE::UI);

	bool res = __super::Initialize();
	assert(res);

	return true;
}

void InstructionWorld::Finalize()
{
	World::Finalize();
}


void InstructionWorld::Enter()
{
	std::cout << "InstructionWorld Enter" << std::endl;

	EventManager::GetInstance()->RegisterListener(eEventType::ChangeWorldToMain, dynamic_cast<EventListener*>(this));

	this->Initialize();
}

void InstructionWorld::Exit()
{
	std::cout << "InstructionWorld Exit" << std::endl;

	this->Finalize();
}

void InstructionWorld::HandleEvent(Event* event)
{
	if(event->eventID == eEventType::ChangeWorldToMain)
	{
		m_pWorldManager->ChangeWorld(WORLD_TYPE::MAIN);
	}
}