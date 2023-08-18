#pragma once
#include "ItemBoxObject.h"
#include "Spawner.h"
#include "../Engine/EventListener.h"

enum class eItemBoxType;

class ItemBoxObject;

class ItemSpawner
	: public Spawner
	, public EventListener
{
	int m_curCount[static_cast<UINT>(eItemBoxType::END_ITEMBOX)] = {};

	float elapsedTime = 0;

	ItemBoxObject* m_pSpawnObject = nullptr;

	eItemBoxType m_itemBoxType;

public:
	bool Initialize() final;
	void Update(const float deltaTime) final;

public:
	void SetType(eItemBoxType itemType);
	void RandomSpawn();

	void HandleEvent(Event* event) final;
};