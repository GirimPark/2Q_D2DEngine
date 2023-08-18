#include "framework.h"
#include "InGameWorld.h"

#include <random>

#include "ItemBoxObject.h"
#include "ItemObject.h"
#include "ShoeItem.h"
#include "InGameUIObject.h"
#include "PlayerObject.h"
#include "MoneyObject.h"
#include "MoneySpawner.h"
#include "ItemSpawner.h"
#include "PlayerFSM1.h"
#include "../Engine/CollisionManager.h"

#include "../Engine/Event.h"
#include "../Engine/EventManager.h"
#include "../Engine/WorldManager.h"

InGameWorld::~InGameWorld()
{
	if(m_pPlayerFSM)
	{
		delete m_pPlayerFSM;
		m_pPlayerFSM = nullptr;
	}
}

bool InGameWorld::Initialize()
{
	m_pPlayerObject1 = CreateGameObject<PlayerObject>(L"Player1", GROUP_TYPE::PLAYER);

	m_pInGameUIObject = CreateGameObject<InGameUIObject>(L"MainUIObject", GROUP_TYPE::UI);

	m_pMoneySpawner = CreateGameObject<MoneySpawner>(L"Spawner", GROUP_TYPE::SPAWNER);
	m_pMoneySpawner->SetType(eMoneyType::SPAWNED);  
	//m_pMoneySpawner->SetItemSpawnArea({150, 660, 540, 920});
	m_pMoneySpawner->SetItemSpawnArea({180, 690, 510, 890});
	m_pMoneySpawner->SetItemCount(10);
	m_pMoneySpawner->SetScale(30);
	m_pMoneySpawner->SetItemSpawnTime(1.f);

	m_pItemThrowSpawner = CreateGameObject<ItemSpawner>(L"Spawner", GROUP_TYPE::SPAWNER);
	m_pItemThrowSpawner->SetType(eItemBoxType::THROW);
	//m_pItemThrowSpawner->SetItemSpawnArea({ 540, 100, 1490, 380 });
	m_pItemThrowSpawner->SetItemSpawnArea({ 580, 140, 1450, 340 });
	//m_pItemThrowSpawner->SetItemSpawnArea({ 890, 380,1770, 660 });
	m_pItemThrowSpawner->SetItemSpawnArea({ 930, 420,1730, 620 });
	m_pItemThrowSpawner->SetItemCount(4);
	m_pItemThrowSpawner->SetScale(40);
	m_pItemThrowSpawner->SetItemSpawnTime(1.f);

	m_pItemInstallationSpawner = CreateGameObject<ItemSpawner>(L"Spawner", GROUP_TYPE::SPAWNER);
	m_pItemInstallationSpawner->SetType(eItemBoxType::INSTALLATION);
	//m_pItemInstallationSpawner->SetItemSpawnArea({ 890, 380, 1490, 1080 });
	m_pItemInstallationSpawner->SetItemSpawnArea({ 930, 420, 1450, 1040 });
	m_pItemInstallationSpawner->SetItemCount(4);
	m_pItemInstallationSpawner->SetScale(40);
	m_pItemInstallationSpawner->SetItemSpawnTime(1.f);

	m_pItemReinforcedSpawner = CreateGameObject<ItemSpawner>(L"Spawner", GROUP_TYPE::SPAWNER);
	m_pItemReinforcedSpawner->SetType(eItemBoxType::REINFORCED);
	//m_pItemReinforcedSpawner->SetItemSpawnArea({ 540, 380, 1490, 660 });
	m_pItemReinforcedSpawner->SetItemSpawnArea({ 580, 420, 1450, 620 });
	//m_pItemReinforcedSpawner->SetItemSpawnArea({ 540, 660,890, 1080 });
	m_pItemReinforcedSpawner->SetItemSpawnArea({ 580, 700,850, 1040 });
	//m_pItemReinforcedSpawner->SetItemSpawnArea({ 1490, 660,1770, 920 });
	m_pItemReinforcedSpawner->SetItemSpawnArea({ 1530, 700,1730, 880 });
	m_pItemReinforcedSpawner->SetItemCount(4);
	m_pItemReinforcedSpawner->SetScale(40);
	m_pItemReinforcedSpawner->SetItemSpawnTime(1.f);

	bool res = __super::Initialize();
	assert(res);

	// Player FSM Attach
	m_pPlayerFSM = new PlayerFSM1;
	m_pPlayerObject1->AttachFSM(m_pPlayerFSM);

	// SetLocation
	m_pPlayerObject1->SetLocation(ScreenWidth / 2.f - 300.f, ScreenHeight / 2.f);

	// CollisionManager
	m_pCollisionManager->EnableCollisionType(GROUP_TYPE::PLAYER, GROUP_TYPE::MONEY);
	m_pCollisionManager->EnableCollisionType(GROUP_TYPE::PLAYER, GROUP_TYPE::ITEMBOX);

	/// 사용할 아이템 설정
	m_ItemList[0].resize(static_cast<int>(eItemType::THROW_END) - static_cast<int>(eItemType::THROW_START) - 1);
	m_ItemList[1].resize(static_cast<int>(eItemType::INSTALLATION_END) - static_cast<int>(eItemType::INSTALLATION_START) - 1);
	m_ItemList[2].resize(static_cast<int>(eItemType::REINFORCED_END) - static_cast<int>(eItemType::REINFORCED_START) - 1);

	int assignItem = static_cast<int>(eItemType::THROW_START) + 1;
	for (size_t i = 0; i < m_ItemList[0].size(); i++)
	{
		m_ItemList[0][i] = static_cast<eItemType>(assignItem);
		++assignItem;
	}
	assignItem = static_cast<int>(eItemType::INSTALLATION_START) + 1;
	for (size_t i = 0; i < m_ItemList[1].size(); i++)
	{
		m_ItemList[1][i] = static_cast<eItemType>(assignItem);
		++assignItem;
	}
	assignItem = static_cast<int>(eItemType::REINFORCED_START) + 1;
	for (size_t i = 0; i < m_ItemList[2].size(); i++)
	{
		m_ItemList[2][i] = static_cast<eItemType>(assignItem);
		++assignItem;
	}


	return true;
}

void InGameWorld::Finalize()
{
	if (m_pPlayerFSM)
	{
		delete m_pPlayerFSM;
		m_pPlayerFSM = nullptr;
	}

	World::Finalize();
}


void InGameWorld::Enter()
{
	std::cout << "InGameWorld Enter" << std::endl;

	EventManager::GetInstance()->RegisterListener(eEventType::DeleteGameObject, dynamic_cast<EventListener*>(this));

	this->Initialize();
}

void InGameWorld::Exit()
{
	std::cout << "InGameWorld Exit" << std::endl;

	this->Finalize();
}

eItemType InGameWorld::GetRandomItem(eItemBoxType itemType)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	if (itemType == eItemBoxType::THROW)
	{
		std::uniform_int_distribution<> dis(0, static_cast<int>(m_ItemList[0].size() - 1));
		return m_ItemList[static_cast<UINT>(itemType)][dis(gen)];
	}
	if (itemType == eItemBoxType::INSTALLATION)
	{
		std::uniform_int_distribution<> dis(0, static_cast<int>(m_ItemList[1].size() - 1));
		return m_ItemList[static_cast<UINT>(itemType)][dis(gen)];
	}
	if (itemType == eItemBoxType::REINFORCED)
	{
		std::uniform_int_distribution<> dis(0, static_cast<int>(m_ItemList[2].size() - 1));
		return m_ItemList[static_cast<UINT>(itemType)][dis(gen)];
	}
	return eItemType::NOTHING;
}

void InGameWorld::HandleEvent(Event* event)
{
	if (event->eventID == eEventType::DeleteGameObject)
	{
		DeleteGameObject(event->objGroup, event->obj);
	}
}