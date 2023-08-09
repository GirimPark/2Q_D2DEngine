#include "framework.h"
#include "PlayerObject.h"

#include "PlayerFSM.h"

#include "../Engine/BoxComponent.h"
#include "../Engine/AnimationComponent.h"
#include "../Engine/MovementComponent.h"
#include "../Engine/FSMComponent.h"
#include "../Engine/DirectionComponent.h"
#include "../Engine/EventManager.h"

#include <vector>

PlayerObject::~PlayerObject()
{
	delete m_pPlayerFSM;
}

bool PlayerObject::Initialize()
{
	// AnimationComponent
	m_pAnimComponent = CreateComponent<AnimationComponent>(L"AnimationComponent");
	std::vector<framework::FRAME_INFO> playerFrame;
	// todo(채원) : Animation Load 사용성 개선
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

	m_pAnimComponent->SetRelativeLocation(ScreenWidth / 2.f, ScreenHeight / 2.f);
	SetRootComponent(m_pAnimComponent);
	// Default State를 지정해주기 위한 Listener 등록
	EventManager::GetInstance()->RegisterListener(eEventType::SetDefaultAnimation, dynamic_cast<EventListener*>(m_pAnimComponent));
	// 이후 애니메이션 change를 위한 Listener 등록
	EventManager::GetInstance()->RegisterListener(eEventType::ChangeCurAnimation, dynamic_cast<EventListener*>(m_pAnimComponent));

	// MovementComponent
	m_pMovementComponent = CreateComponent<MovementComponent>(L"MovementComponent");
	
	// FSMComponent
	m_pFSMComponent = CreateComponent<FSMComponent>(L"FSMComponent");
	m_pPlayerFSM = new PlayerFSM;
	m_pFSMComponent->AttachFSM(m_pPlayerFSM, m_pAnimComponent);
	EventManager::GetInstance()->RegisterListener(eEventType::AnimationEnd, dynamic_cast<EventListener*>(m_pPlayerFSM));

	m_pDirectionComponent = CreateComponent<DirectionComponent>(L"DirectionComponent");
	m_pDirectionComponent->SetColor(D2D1::ColorF::Yellow);
	m_pDirectionComponent->AttachToComponent(m_pAnimComponent);
	 
	bool res = __super::Initialize();
	assert(res);

	return true;
}

void PlayerObject::Update(const float deltaTime)
{
	__super::Update(deltaTime);
}
