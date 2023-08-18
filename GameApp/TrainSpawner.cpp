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
	// 스폰을 위한 경과 시간 증가
	m_ElapsedSpawnTime += deltaTime;

	// 딜레이 시작
	if(m_ElapsedSpawnTime >= m_SpawnTime)
	{
		// std::wcout << m_name << "에서 -> " << m_DelayTime << "초 후에 기차가 스폰됩니다..!" << std::endl;

		// 딜레이를 위한 경과 시간 증가
		m_ElaspedDelayTime += deltaTime;

		// 기차 생성
		if(m_ElaspedDelayTime >= m_DelayTime)
		{
			m_ElaspedDelayTime = 0.f;
			m_ElapsedSpawnTime = 0.f;

			// 랜덤 클래스 사용
			std::random_device rd;
			std::mt19937 gen(rd());
			std::uniform_int_distribution<> dis(5, 15);
			std::uniform_int_distribution<> dis2(0, 1);
			std::uniform_int_distribution<> dis3(300, 700);
			std::uniform_int_distribution<> dis4(0, 2);

			// 랜덤값 생성
			const int randSpawnTime = dis(gen);
			const int randPosNum = dis2(gen);
			const int randSpeed = dis3(gen);
			const int randDropTypeNum = dis4(gen);

			// 기차 스폰 시간 재설정
			m_SpawnTime = static_cast<float>(randSpawnTime);

			// 기차 생성
			TrainObstacle* trainObstacle = m_pOwnerWorld->CreateGameObject<TrainObstacle>(L"TrainObstacle_Clone", GROUP_TYPE::OBSTACLE);

			// 기차 생성 위치 설정
			// trainObstacle->SetLocation(m_SpawnPositions[randPosNum].x, m_SpawnPositions[randPosNum].y);
			trainObstacle->SetSpawnPosition(m_SpawnPositions[randPosNum].x, m_SpawnPositions[randPosNum].y);

			// 기차의 이동 방향
			if (m_SpawnPositions[randPosNum].y < 0)
				trainObstacle->SetDirection(1);
			else if (m_SpawnPositions[randPosNum].y > ScreenHeight)
				trainObstacle->SetDirection(-1);

			// 기차 컴포넌트 부착 및 초기화 타이밍
			trainObstacle->Initialize();

			// 기차의 이미지 반전 설정
			if (m_SpawnPositions[randPosNum].y < 0)
				dynamic_cast<TextureComponent*>(trainObstacle->GetRootComponent())->SetFlipY(true);
			else if (m_SpawnPositions[randPosNum].y > ScreenHeight)
				dynamic_cast<TextureComponent*>(trainObstacle->GetRootComponent())->SetFlipY(false);

			// 기차의 스피드 설정
			trainObstacle->SetSpeed(static_cast<float>(randSpeed));

			// 기차의 드롭 타입 설정
			trainObstacle->SetDropType(m_DropTypeArr[randDropTypeNum]);
		}
	}

	// 컴포넌트 업데이트
	GameObject::Update(deltaTime);
}