#pragma once

#include "ItemObject.h"
#include "ItemBoxObject.h"
#include "../Engine/EventListener.h"
#include "../Engine/World.h"

class PlayerFSM1;
class ShoeItem;
class PlayerObject;
class ItemSpawner;
class InGameUIObject;
class MoneyObject;
class ItemBoxObject;
class MoneySpawner;

class InGameWorld
	: public World
	, public EventListener
{
private:
	InGameUIObject* m_pInGameUIObject = nullptr;

	PlayerObject* m_pPlayerObject1 = nullptr;
	PlayerFSM1* m_pPlayerFSM = nullptr;

	MoneySpawner* m_pMoneySpawner = nullptr;
	ItemSpawner* m_pItemThrowSpawner = nullptr;
	ItemSpawner* m_pItemInstallationSpawner = nullptr;
	ItemSpawner* m_pItemReinforcedSpawner = nullptr;

	std::vector<eItemType> m_ItemList[static_cast<UINT>(eItemBoxType::END_ITEMBOX)];

public:
	~InGameWorld();
	bool Initialize() final;
	void Finalize() final;

	void Enter() final;
	void Exit() final;

	eItemType GetRandomItem(eItemBoxType itemType);

	void HandleEvent(Event* event) final;
};
