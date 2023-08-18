#include "framework.h"
#include "TrainObstacle.h"

#include "../Engine/TextureComponent.h"
#include "../Engine/BoxComponent.h"
#include "../Engine/BoxCollider2D.h"

#include "../Engine/CommonApp.h"
#include "../Engine/EventManager.h"

TrainObstacle::TrainObstacle()
{
}

TrainObstacle::~TrainObstacle()
{
}

bool TrainObstacle::Initialize()
{
	/// TextrueComponent
	m_pTextureComponent = CreateComponent<TextureComponent>(L"TextureComponent");
	m_pTextureComponent->SetTextureAsset(L"../Resource/Test/Train.png", L"TrainTexture");
	m_pTextureComponent->SetRelativeLocation(m_SpawnPosition.x, m_SpawnPosition.y);
	SetRootComponent(m_pTextureComponent);

	/// BoxComponent
	// m_pBoxComponent = CreateComponent<BoxComponent>(L"BoxComponent");
	// SetRootComponent(m_pBoxComponent);

	/// BoxCollider2D
	m_pBoxCollider2D = CreateComponent<BoxCollider2D>(L"BoxCollider2D");
	m_pBoxCollider2D->SetRelativeLocation(-10.f, 5.f);
	m_pBoxCollider2D->SetExtend(70.f, 427.f);
	m_pBoxCollider2D->AttachToComponent(m_pTextureComponent);

	/// BoxCollider2D
	m_pHeadBoxCollider = CreateComponent<BoxCollider2D>(L"BoxCollider2D_Head");
	m_pHeadBoxCollider->SetRelativeLocation(-10.f, m_Direction * 427.f);
	m_pHeadBoxCollider->SetExtend(70.f, 10.f);
	m_pHeadBoxCollider->AttachToComponent(m_pTextureComponent);

	const bool res = GameObject::Initialize();
	assert(res);

	return true;
}

void TrainObstacle::Update(const float deltaTime)
{
	const float extendY = dynamic_cast<BoxCollider2D*>(this->GetComponent<Collider2D>())->GetExtend().y;

	// 만약 화면 벗어나면 삭제
	if(this->GetRootComponent()->GetWorldLocation().y > ScreenHeight)
	{
		// 기차 삭제
		if (this->GetRootComponent()->GetWorldLocation().y - extendY > ScreenHeight)
		{
			EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::OBSTACLE, this);
			return;
		}
	}
	else if(this->GetRootComponent()->GetWorldLocation().y < 0.f)
	{
		// 기차 삭제
		if (this->GetRootComponent()->GetWorldLocation().y + extendY < 0)
		{
			EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::OBSTACLE, this);
			return;
		}
	}

	// 임시	벡터 생성
	const framework::Vector2D velocity = { 0.f, m_Speed * m_Direction };

	// 기차의 이동
	GetRootComponent()->AddRelativeLocation(velocity * deltaTime);

	// 컴포넌트 업데이트
	GameObject::Update(deltaTime);

}