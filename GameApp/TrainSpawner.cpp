#include "framework.h"
#include "TrainSpawner.h"

#include <locale>

#include "TrainObstacle.h"

#include "../Engine/TextureComponent.h"
#include "../Engine/World.h"

#include <random>

TRAIN_DROP_TYPE TrainSpawner::m_DropTypeArr[3] = { TRAIN_DROP_TYPE::NONE, TRAIN_DROP_TYPE::MONEY, TRAIN_DROP_TYPE::ITEM };

TrainSpawner::TrainSpawner()
{
}

TrainSpawner::~TrainSpawner()
{
}

bool TrainSpawner::Initialize()
{
	const bool res = GameObject::Initialize();
	assert(res);

	return true;
}

void TrainSpawner::Update(const float deltaTime)
{
	// ������ ���� ��� �ð� ����
	m_ElapsedSpawnTime += deltaTime;

	// ������ ����
	if(m_ElapsedSpawnTime >= m_SpawnTime)
	{
		// std::wcout << m_name << "���� -> " << m_DelayTime << "�� �Ŀ� ������ �����˴ϴ�..!" << std::endl;

		// �����̸� ���� ��� �ð� ����
		m_ElaspedDelayTime += deltaTime;

		// ���� ����
		if(m_ElaspedDelayTime >= m_DelayTime)
		{
			m_ElaspedDelayTime = 0.f;
			m_ElapsedSpawnTime = 0.f;

			// ���� Ŭ���� ���
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(5, 15);
			std::uniform_int_distribution<> dis2(0, 1);
			std::uniform_int_distribution<> dis3(300, 700);
			std::uniform_int_distribution<> dis4(0, 2);

			// ������ ����
			const int randSpawnTime = dis(gen);
			const int randPosNum = dis2(gen);
			const int randSpeed = dis3(gen);
			const int randDropTypeNum = dis4(gen);

			// ���� ���� �ð� �缳��
			m_SpawnTime = static_cast<float>(randSpawnTime);

			// ���� ����
			TrainObstacle* trainObstacle = m_pOwnerWorld->CreateGameObject<TrainObstacle>(L"TrainObstacle_Clone", GROUP_TYPE::OBSTACLE);

			// ���� ���� ��ġ ����
			// trainObstacle->SetLocation(m_SpawnPositions[randPosNum].x, m_SpawnPositions[randPosNum].y);
			trainObstacle->SetSpawnPosition(m_SpawnPositions[randPosNum].x, m_SpawnPositions[randPosNum].y);

			// ������ �̵� ����
			if (m_SpawnPositions[randPosNum].y < 0)
				trainObstacle->SetDirection(1);
			else if (m_SpawnPositions[randPosNum].y > ScreenHeight)
				trainObstacle->SetDirection(-1);

			// ���� ������Ʈ ���� �� �ʱ�ȭ Ÿ�̹�
			trainObstacle->Initialize();

			// ������ �̹��� ���� ����
			if (m_SpawnPositions[randPosNum].y < 0)
				dynamic_cast<TextureComponent*>(trainObstacle->GetRootComponent())->SetFlipY(true);
			else if (m_SpawnPositions[randPosNum].y > ScreenHeight)
				dynamic_cast<TextureComponent*>(trainObstacle->GetRootComponent())->SetFlipY(false);

			// ������ ���ǵ� ����
			trainObstacle->SetSpeed(static_cast<float>(randSpeed));

			// ������ ��� Ÿ�� ����
			trainObstacle->SetDropType(m_DropTypeArr[randDropTypeNum]);
		}
	}

	// ������Ʈ ������Ʈ
	GameObject::Update(deltaTime);
}