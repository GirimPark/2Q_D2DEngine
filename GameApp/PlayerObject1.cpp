#include "framework.h"
#include "PlayerObject1.h"

#include "../Engine/BoxComponent.h"
#include "../Engine/AnimationComponent.h"
#include "../Engine/MovementComponent.h"
#include "../Engine/DirectionComponent.h"
#include "../Engine/BoxCollider2D.h"

#include <vector>

PlayerObject1::~PlayerObject1()
{
	// delete m_pPlayerFSM;
}

bool PlayerObject1::Initialize()
{
	/// BoxComponent
	m_pBoxComponent = CreateComponent<BoxComponent>(L"Player1");
	m_pBoxComponent->SetWidth(50.f);
	m_pBoxComponent->SetHeight(50.f);
	m_pBoxComponent->SetColor(D2D1::ColorF::White);
	m_pBoxComponent->SetRelativeLocation(ScreenWidth / 2.f - 400.f, ScreenHeight / 2.f);
	SetRootComponent(m_pBoxComponent);

	/// MovementComponent
	m_pMovementComponent = CreateComponent<MovementComponent>(L"MovementComponent");

	/// DirectionComponent
	m_pDirectionComponent = CreateComponent<DirectionComponent>(L"DirectionComponent");
	m_pDirectionComponent->SetColor(D2D1::ColorF::Yellow);
	m_pDirectionComponent->AttachToComponent(m_pBoxComponent);

	/// BoxCollider2D
	m_pBoxCollider2D = CreateComponent<BoxCollider2D>(L"Collider2D");
	m_pBoxCollider2D->SetExtend(50.f, 50.f);
	m_pBoxCollider2D->SetColor(D2D1::ColorF::SkyBlue);
	m_pBoxCollider2D->AttachToComponent(m_pBoxComponent);


	bool res = GameObject::Initialize();
	assert(res);

	return true;
}

void PlayerObject1::Update(const float deltaTime)
{
	GameObject::Update(deltaTime);
}
