#include "framework.h"
#include "MoneySpawner.h"

#include "MoneyObject.h"

#include <random>

#include "../Engine/World.h"
#include "../Engine/EventManager.h"


class Event;

bool MoneySpawner::Initialize()
{
	EventManager::GetInstance()->RegisterListener(eEventType::DeleteMoney, this);
	__super::Initialize();

	return true;
}

void MoneySpawner::Update(const float deltaTime)
{
	__super::Update(deltaTime);
	if (m_curCount == m_maxCount)
		return;

	m_gameObjectList = m_pOwnerWorld->GetGameObjectGroup(GROUP_TYPE::MONEY);

	static float elapsedTime = 0;

	if(!m_bCheckAABB)
		elapsedTime += deltaTime;

	if (elapsedTime >= m_spawnTime)
	{
		RandomSpawn();
		elapsedTime = 0.f;
	}
}

void MoneySpawner::SetType(eMoneyType moneyType)
{
	m_moneyType = moneyType;
}

void MoneySpawner::RandomSpawn()
{
	static int cnt = 0;
	static int recallCount = 0;

	// ����Լ��� 15�� �Ҹ��� 
	if (recallCount >= 15)
	{
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, static_cast<UINT>(m_spawnArea.size()) - 1);

	// �������� ���� ����
	size_t curSpawnAreaIndex;
	if (m_spawnArea.size() > 1)
		curSpawnAreaIndex = dis(gen);
	else
		curSpawnAreaIndex = 0;
	m_curSpawnArea = m_spawnArea[curSpawnAreaIndex];

	// ���� ���� ���ϱ�
	std::random_device rd1;
	std::mt19937 gen1(rd1());
	std::uniform_int_distribution<> dis1(static_cast<int>(m_curSpawnArea.left), static_cast<int>(m_curSpawnArea.right));
	m_randX = static_cast<float>(dis1(gen1));

	std::random_device rd2;
	std::mt19937 gen2(rd2());
	std::uniform_int_distribution<> dis2(static_cast<int>(m_curSpawnArea.top), static_cast<int>(m_curSpawnArea.bottom));
	m_randY = static_cast<float>(dis2(gen2));

	if(m_gameObjectList.empty())
	{
		m_pSpawnObject =
			m_pOwnerWorld->CreateGameObject<MoneyObject>(L"Money", GROUP_TYPE::MONEY);
		m_pSpawnObject->Initialize();
		m_pSpawnObject->SetLocation(m_randX, m_randY);
		m_pSpawnObject->SetMoneyType(m_moneyType);

		m_curCount++;
		return;
	}

	float x = 0.f;
	float y = 0.f;

	for (size_t i = 0; i < m_gameObjectList.size(); i++)
	{
		// eMoneyType�� spawn �ܿ� �ٸ��Ŷ��� �Ǻ����� �ʿ� ����.
		if (!(dynamic_cast<MoneyObject*>(m_gameObjectList[i])->GetMoneyType()
			== eMoneyType::SPAWNED))
			continue;
		x =
			dynamic_cast<MoneyObject*>(m_gameObjectList[i])->GetLocation().x;
		y =
			dynamic_cast<MoneyObject*>(m_gameObjectList[i])->GetLocation().y;

		if (CheckSpawnArea(x, y))
		{
			m_bCheckAABB = true;
			break;
		}
		m_bCheckAABB = false;
	}

	if(m_bCheckAABB)
	{
		recallCount++;
		RandomSpawn();
		recallCount = 0;
		m_bCheckAABB = false;
		return;
	}
	else
	{
		m_pSpawnObject =
			m_pOwnerWorld->CreateGameObject<MoneyObject>(L"Money", GROUP_TYPE::MONEY);
		m_pSpawnObject->Initialize();
		m_pSpawnObject->SetLocation(m_randX, m_randY);
		m_pSpawnObject->SetMoneyType(m_moneyType);
		m_bCheckAABB = false;
		m_curCount++;
		recallCount = 0;
		return;
	}
}

void MoneySpawner::HandleEvent(Event* event)
{
	if (event->eventID == eEventType::DeleteMoney && m_moneyType == eMoneyType::SPAWNED)
	{
		m_curCount--;
	}
}
