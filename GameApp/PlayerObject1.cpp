#include "framework.h"
#include "PlayerObject1.h"

#include "PlayerFSM.h"

#include "../Engine/BoxComponent.h"
#include "../Engine/AnimationComponent.h"
#include "../Engine/MovementComponent.h"
#include "../Engine/FSMComponent.h"
#include "../Engine/DirectionComponent.h"
#include "../Engine/BoxCollider2D.h"

#include <vector>

PlayerObject1::~PlayerObject1()
{
	// delete m_pPlayerFSM;
}

bool PlayerObject1::Initialize()
{
	/*
	// AnimationComponent
	m_pAnimComponent = CreateComponent<AnimationComponent>(L"AnimationComponent");
	std::vector<framework::FRAME_INFO> playerFrame;
	// Idle
	playerFrame.push_back(framework::FRAME_INFO({ 3, 698, 61, 787 }, 0.1f));
	playerFrame.push_back(framework::FRAME_INFO({ 73, 696, 130, 787 }, 0.1f));
	playerFrame.push_back(framework::FRAME_INFO({ 143, 695, 197, 787 }, 0.1f));
	playerFrame.push_back(framework::FRAME_INFO({ 279, 698, 337, 787 }, 0.1f));
	playerFrame.push_back(framework::FRAME_INFO({ 347, 699, 406, 787 }, 0.1f));
	m_pAnimComponent->SetAnimationAsset(L"../Resource/ken.png", L"IDLE", playerFrame);
	// Move
	playerFrame.clear();
	playerFrame.push_back(framework::FRAME_INFO({ 9,883,61,965 }, 0.1f));
	playerFrame.push_back(framework::FRAME_INFO({ 71,878,130,965 }, 0.1f));
	playerFrame.push_back(framework::FRAME_INFO({ 141,877,204,966 }, 0.1f));
	playerFrame.push_back(framework::FRAME_INFO({ 216,876,278,964 }, 0.1f));
	playerFrame.push_back(framework::FRAME_INFO({ 358,878,407,966 }, 0.1f));
	m_pAnimComponent->SetAnimationAsset(L"../Resource/ken.png", L"MOVE", playerFrame);

	m_pAnimComponent->SetCurAnimation(L"IDLE", false);
	m_pAnimComponent->SetRelativeLocation(512.f, 384.f);
	SetRootComponent(m_pAnimComponent);
	*/

	/// BoxComponent
	m_pBoxComponent = CreateComponent<BoxComponent>(L"Player1");
	m_pBoxComponent->SetWidth(50.f);
	m_pBoxComponent->SetHeight(50.f);
	m_pBoxComponent->SetColor(D2D1::ColorF::White);
	m_pBoxComponent->SetRelativeLocation(ScreenWidth / 2.f - 400.f, ScreenHeight / 2.f);
	SetRootComponent(m_pBoxComponent);

	/// MovementComponent
	m_pMovementComponent = CreateComponent<MovementComponent>( L"MovementComponent");

	/*
	// FSMComponent
	m_pFSMComponent = CreateComponent<FSMComponent>(L"FSMComponent");
	m_pPlayerFSM = new PlayerFSM;
	m_pFSMComponent->AttachFSM(m_pPlayerFSM, m_pAnimComponent);
	*/

	/// DirectionComponent
	m_pDirectionComponent = CreateComponent<DirectionComponent>(L"DirectionComponent");
	m_pDirectionComponent->SetColor(D2D1::ColorF::Yellow);
	m_pDirectionComponent->AttachToComponent(m_pBoxComponent);

	/// BoxCollider2D
	m_pBoxCollider2D = CreateComponent<BoxCollider2D>(L"BoxCollider2D");
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
