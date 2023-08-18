#include "framework.h"
#include "PlayerObject.h"

#include "BottleItem.h"
#include "InGameWorld.h"
#include "ItemBoxObject.h"
#include "MoneyObject.h"
#include "PunchItem.h"
#include "ShoeItem.h"
#include "SnowItem.h"
#include "TestWorld.h"
#include "TrapItem.h"
#include "WaveItem.h"
#include "ProjectileObject.h"

#include "../Engine/InputManager.h"
#include "../Engine/EventManager.h"
#include "../Engine/AnimationComponent.h"
#include "../Engine/PlayerMovement.h"
#include "../Engine/FSMComponent.h"
#include "../Engine/DirectionComponent.h"
#include "../Engine/BoxCollider2D.h"
#include "../Engine/World.h"

PlayerObject::~PlayerObject()
{
}

bool PlayerObject::Initialize()
{
	// 플레이어 번호 설정
	if (this->m_name == L"Player1")
		m_PlayerNumber = 0;
	else if (this->m_name == L"Player2")
		m_PlayerNumber = 1;
	else if (this->m_name == L"Player3")
		m_PlayerNumber = 2;
	else if (this->m_name == L"Player4")
		m_PlayerNumber = 3;

	// 가진 아이템 초기화
	for(auto& item : m_OwnedItem)
		item = eItemType::NOTHING;

	// AnimationComponent
	m_pAnimComponent = CreateComponent<AnimationComponent>(L"AnimationComponent");
	InitAnimationAsset();	// SetAnimationAsset
	m_pAnimComponent->SetRelativeLocation(ScreenWidth / 2.f, ScreenHeight / 2.f);
	SetRootComponent(m_pAnimComponent);
	//m_pAnimComponent->LoadAnimationAsset(L"../Resource/ken.png", L"../Resource/TestWorld.WorldAsset");
// Idle
//playerFrame.push_back(framework::FRAME_INFO({ 3, 698, 61, 787 }, 0.1f));
//playerFrame.push_back(framework::FRAME_INFO({ 73, 696, 130, 787 }, 0.1f));
//playerFrame.push_back(framework::FRAME_INFO({ 143, 695, 197, 787 }, 0.1f));
//playerFrame.push_back(framework::FRAME_INFO({ 279, 698, 337, 787 }, 0.1f));
//playerFrame.push_back(framework::FRAME_INFO({ 347, 699, 406, 787 }, 0.1f));
//m_pAnimComponent->SetAnimationAsset(L"../Resource/ken.png", L"IDLE", playerFrame);
//// Move
//playerFrame.clear();
//playerFrame.push_back(framework::FRAME_INFO({ 9,883,61,965 }, 0.1f));
//playerFrame.push_back(framework::FRAME_INFO({ 71,878,130,965 }, 0.1f));
//playerFrame.push_back(framework::FRAME_INFO({ 141,877,204,966 }, 0.1f));
//playerFrame.push_back(framework::FRAME_INFO({ 216,876,278,964 }, 0.1f));
//playerFrame.push_back(framework::FRAME_INFO({ 358,878,407,966 }, 0.1f));
//m_pAnimComponent->SetAnimationAsset(L"../Resource/ken.png", L"MOVE", playerFrame);

	// PlayerMovement
	m_pMovementComponent = CreateComponent<PlayerMovement>(L"PlayerMovement");

	// FSMComponent - AttatchFSM은 아래 인스턴스화한 Player에서 한다
	m_pFSMComponent = CreateComponent<FSMComponent>(L"FSMComponent");

	// DirectionComponent
	m_pDirectionComponent = CreateComponent<DirectionComponent>(L"DirectionComponent");
	m_pDirectionComponent->SetColor(D2D1::ColorF::Yellow);
	m_pDirectionComponent->AttachToComponent(m_pAnimComponent);

	// BoxColliderComponent_Full
	m_pBoxColliderFull = CreateComponent<BoxCollider2D>(L"BoxCollider2D");
	m_pBoxColliderFull->SetRelativeLocation(0.f, 25.f);
	m_pBoxColliderFull->SetExtend(30.f, 25.f);
	m_pBoxColliderFull->AttachToComponent(m_pAnimComponent);

	// BoxColliderComponent_Part
	m_pBoxColliderPart = CreateComponent<BoxCollider2D>(L"PartBoxCollider");
	m_pBoxColliderPart->SetCollisionType(COLLISION_TPYE::NONE);	// TODO : ** 임시 비활성화 **
	m_pBoxColliderPart->SetRelativeLocation(0.f, 30.f);
	m_pBoxColliderPart->SetExtend(10.f, 15.f);
	m_pBoxColliderPart->AttachToComponent(m_pAnimComponent);

	// Event Listener Register
	EventManager::GetInstance()->RegisterListener(eEventType::P1SetDefaultAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P1KeepAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P1ChangeAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P2SetDefaultAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P2KeepAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P2ChangeAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P3SetDefaultAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P3KeepAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P3ChangeAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P4SetDefaultAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P4KeepAnimation, dynamic_cast<EventListener*>(this));
	EventManager::GetInstance()->RegisterListener(eEventType::P4ChangeAnimation, dynamic_cast<EventListener*>(this));

	const bool res = GameObject::Initialize();
	assert(res);

	return true;
}

void PlayerObject::Update(const float deltaTime)
{
	// 살아있을 때만 실행
	if (!IsDead())
	{
		// Test Code
		if (this->GetRootComponent()->GetWorldLocation().x > ScreenWidth || this->GetRootComponent()->GetWorldLocation().x < 0 ||
			this->GetRootComponent()->GetWorldLocation().y > ScreenHeight || this->GetRootComponent()->GetWorldLocation().y < 0)
		{
			this->SetLocation(300.f, 300.f);
		}

		if (m_OwnedItem[static_cast<UINT>(eItemBoxType::THROW)] != eItemType::NOTHING
			&& (InputManager::GetInstance()->IsRightTriggerPush(m_PlayerNumber)
				|| InputManager::GetInstance()->IsPadButtonPush(m_PlayerNumber, GamePadButtonCode::X)))
		{
			UseThrowItem();
		}
		if (m_OwnedItem[static_cast<UINT>(eItemBoxType::INSTALLATION)] != eItemType::NOTHING
			&& InputManager::GetInstance()->IsPadButtonPush(m_PlayerNumber, GamePadButtonCode::A))
		{
			UseInstallationItem();
		}
		if (m_OwnedItem[static_cast<UINT>(eItemBoxType::REINFORCED)] != eItemType::NOTHING
			&& InputManager::GetInstance()->IsPadButtonPush(m_PlayerNumber, GamePadButtonCode::B))
		{
			UseReinforcedItem();
		}

		// 아이템 투척
		if (InputManager::GetInstance()->IsRightTriggerPush(m_PlayerNumber) ||
			InputManager::GetInstance()->IsLeftTriggerPush(m_PlayerNumber))
		{
			auto* projectile = GetOwnerWorld()->CreateGameObject<ProjectileObject>(L"Projectile_Clone", GROUP_TYPE::ITEM);

			// 아이템의 소유자 설정
			projectile->SetOwnerPlayer(this);

			// 속도 변경
			projectile->SetSpeed(500.f);

			// 방향 설정
			const framework::Vector2D tempLookDir = dynamic_cast<PlayerMovement*>(GetComponent(L"PlayerMovement"))->GetLookDir();
			projectile->SetDirection(tempLookDir);

			// 위치 설정
			const framework::Vector2D pos = GetRootComponent()->GetRelativeLocation();
			constexpr float distance = 65.f;
			const framework::Vector2D distVec = tempLookDir * distance;
			projectile->SetPosition(pos + distVec);

			projectile->Initialize();
		}
	}
	else
	{
		std::cout << "Player is Dead !!! -> 스폰지역으로 날라가자" << std::endl;
	}

	// 플레이어 컴포넌트 업데이트
	GameObject::Update(deltaTime);
}

void PlayerObject::OnCollisionEnter(Collider2D* otherCollision)
{
	if (otherCollision->GetName() == L"BoxCollider2D_Head")
	{
		// Kill Player
		KillPlayer();

		// Off All Collider
		std::vector<Collider2D*> thiscolliders = this->GetComponents<Collider2D>();
		for (auto thisCollider : thiscolliders)
		{
			thisCollider->SetCollisionType(COLLISION_TPYE::NONE);
			thisCollider->TurnOff_IsCollision(otherCollision);
		}

		// Respawn Player
		// 플레이어를 어떻게 날리지?
		// 플레이어에 부울값 두기..?
		this->SetLocation(300.f, 300.f);

		return;
	}
}

void PlayerObject::OnCollisionStay(Collider2D* otherCollision)
{
	if (otherCollision->GetOwner()->GetName() == L"TrainObstacle_Clone")
		InputManager::SetControllerVib(m_PlayerNumber, 65535, 65535);
}

void PlayerObject::OnCollisionExit(Collider2D* otherCollision)
{
	if (otherCollision->GetOwner()->GetName() == L"TrainObstacle_Clone")
		InputManager::SetControllerVib(m_PlayerNumber, 0, 0);
}

void PlayerObject::OnTriggerEnter(Collider2D* otherCollision)
{
	ItemBoxObject* castedObj = dynamic_cast<ItemBoxObject*>(otherCollision->GetOwner());
	MoneyObject* castedObj2 = dynamic_cast<MoneyObject*>(otherCollision->GetOwner());

	// ItemBox와 충돌
	if (castedObj)
	{
		if (GetRandomItem(castedObj->GetItemBoxType()))
		{
			EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::ITEMBOX, otherCollision->GetOwner());
			EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject);

			if(castedObj->GetItemBoxType() == eItemBoxType::THROW)
			{
				EventManager::GetInstance()->SendEvent(eEventType::DeleteThrow);
				EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::ITEMBOX, otherCollision->GetOwner());
			}
			else if (castedObj->GetItemBoxType() == eItemBoxType::REINFORCED)
			{
				EventManager::GetInstance()->SendEvent(eEventType::DeleteReinforced);
				EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::ITEMBOX, otherCollision->GetOwner());
			}
			else if (castedObj->GetItemBoxType() == eItemBoxType::INSTALLATION)
			{
				EventManager::GetInstance()->SendEvent(eEventType::DeleteInstallation);
				EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::ITEMBOX, otherCollision->GetOwner());
			}
		}

		// Exit 처리 해주기
		this->GetComponent<BoxCollider2D>()->TurnOff_IsTrigger(otherCollision);
		otherCollision->OnTriggerExit(this->GetComponent<BoxCollider2D>());
	}
	// MoneyObject와 충돌
	else if(castedObj2)
	{
		EventManager::GetInstance()->SendEvent(eEventType::DeleteMoney);
		EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::MONEY, otherCollision->GetOwner());

		// Exit 처리 해주기
		this->GetComponent<BoxCollider2D>()->TurnOff_IsTrigger(otherCollision);
		otherCollision->OnTriggerExit(this->GetComponent<BoxCollider2D>());
	}
}

void PlayerObject::OnTriggerStay(Collider2D* otherCollision)
{
	// InputManager::SetControllerVib(m_PlayerNumber, 65535, 65535);
}

void PlayerObject::OnTriggerExit(Collider2D* otherCollision)
{
	// InputManager::SetControllerVib(m_PlayerNumber, 0, 0);
}

void PlayerObject::HandleEvent(Event* event)
{
	if(this->m_name == L"Player1")
	{
		if (event->eventID == eEventType::P1KeepAnimation)
		{
			m_pAnimComponent->KeepAnimation(event->animationInfo.flip);
			return;
		}
		if (event->eventID == eEventType::P1ChangeAnimation)
		{
			m_pAnimComponent->ChangeAnimation(event->animationInfo.animationName, event->animationInfo.flip);
			return;
		}
		if (event->eventID == eEventType::P1SetDefaultAnimation)
		{
			m_pAnimComponent->SetAnimationName(event->animationInfo.animationName);
			return;
		}
	}
	if (this->m_name == L"Player2")
	{
		if (event->eventID == eEventType::P2KeepAnimation)
		{
			m_pAnimComponent->KeepAnimation(event->animationInfo.flip);
			return;
		}
		if (event->eventID == eEventType::P2ChangeAnimation)
		{
			m_pAnimComponent->ChangeAnimation(event->animationInfo.animationName, event->animationInfo.flip);
			return;
		}
		if (event->eventID == eEventType::P2SetDefaultAnimation)
		{
			m_pAnimComponent->SetAnimationName(event->animationInfo.animationName);
			return;
		}
	}
	if (this->m_name == L"Player3")
	{
		if (event->eventID == eEventType::P3KeepAnimation)
		{
			m_pAnimComponent->KeepAnimation(event->animationInfo.flip);
			return;
		}
		if (event->eventID == eEventType::P3ChangeAnimation)
		{
			m_pAnimComponent->ChangeAnimation(event->animationInfo.animationName, event->animationInfo.flip);
			return;
		}
		if (event->eventID == eEventType::P3SetDefaultAnimation)
		{
			m_pAnimComponent->SetAnimationName(event->animationInfo.animationName);
			return;
		}
	}
	if (this->m_name == L"Player4")
	{
		if (event->eventID == eEventType::P4KeepAnimation)
		{
			m_pAnimComponent->KeepAnimation(event->animationInfo.flip);
			return;
		}
		if (event->eventID == eEventType::P4ChangeAnimation)
		{
			m_pAnimComponent->ChangeAnimation(event->animationInfo.animationName, event->animationInfo.flip);
			return;
		}
		if (event->eventID == eEventType::P4SetDefaultAnimation)
		{
			m_pAnimComponent->SetAnimationName(event->animationInfo.animationName);
			return;
		}
	}
}

void PlayerObject::AttachFSM(FSM* fsm)
{
	m_pFSMComponent->AttachFSM(fsm);
}

void PlayerObject::InitAnimationAsset()
{
	std::vector<framework::FRAME_INFO> frame_IdleBack;
	frame_IdleBack.push_back(framework::FRAME_INFO({ 0, 0, 80, 110 }, 0.1f));
	frame_IdleBack.push_back(framework::FRAME_INFO({ 80, 0, 160, 110 }, 0.1f));
	frame_IdleBack.push_back(framework::FRAME_INFO({ 160, 0, 240, 110 }, 0.1f));
	frame_IdleBack.push_back(framework::FRAME_INFO({ 240, 0, 320, 110 }, 0.1f));

	std::vector<framework::FRAME_INFO> frame_IdleFront;
	frame_IdleFront.push_back(framework::FRAME_INFO({ 0, 110, 80, 220 }, 0.1f));
	frame_IdleFront.push_back(framework::FRAME_INFO({ 80, 110, 160, 220 }, 0.1f));
	frame_IdleFront.push_back(framework::FRAME_INFO({ 160, 110, 240, 220 }, 0.1f));
	frame_IdleFront.push_back(framework::FRAME_INFO({ 240, 110, 320, 220 }, 0.1f));

	std::vector<framework::FRAME_INFO> frame_IdleSide;
	frame_IdleSide.push_back(framework::FRAME_INFO({ 0, 220, 80, 330 }, 0.1f));
	frame_IdleSide.push_back(framework::FRAME_INFO({ 80, 220, 160, 330 }, 0.1f));
	frame_IdleSide.push_back(framework::FRAME_INFO({ 160, 220, 240, 330 }, 0.1f));
	frame_IdleSide.push_back(framework::FRAME_INFO({ 240, 220, 320, 330 }, 0.1f));

	std::vector<framework::FRAME_INFO> frame_MoveBack;
	frame_MoveBack.push_back(framework::FRAME_INFO({ 0, 330, 80, 440 }, 0.1f));
	frame_MoveBack.push_back(framework::FRAME_INFO({ 80, 330, 160, 440 }, 0.1f));
	frame_MoveBack.push_back(framework::FRAME_INFO({ 160, 330, 240, 440 }, 0.1f));
	frame_MoveBack.push_back(framework::FRAME_INFO({ 240, 330, 320, 440 }, 0.1f));
	frame_MoveBack.push_back(framework::FRAME_INFO({ 320, 330, 400, 440 }, 0.1f));
	frame_MoveBack.push_back(framework::FRAME_INFO({ 400, 330, 480, 440 }, 0.1f));
	frame_MoveBack.push_back(framework::FRAME_INFO({ 480, 330, 560, 440 }, 0.1f));
	frame_MoveBack.push_back(framework::FRAME_INFO({ 560, 330, 640, 440 }, 0.1f));

	std::vector<framework::FRAME_INFO> frame_MoveFront;
	frame_MoveFront.push_back(framework::FRAME_INFO({ 0, 440, 80, 550 }, 0.1f));
	frame_MoveFront.push_back(framework::FRAME_INFO({ 80, 440, 160, 550 }, 0.1f));
	frame_MoveFront.push_back(framework::FRAME_INFO({ 160, 440, 240, 550 }, 0.1f));
	frame_MoveFront.push_back(framework::FRAME_INFO({ 240, 440, 320, 550 }, 0.1f));
	frame_MoveFront.push_back(framework::FRAME_INFO({ 320, 440, 400, 550 }, 0.1f));
	frame_MoveFront.push_back(framework::FRAME_INFO({ 400, 440, 480, 550 }, 0.1f));
	frame_MoveFront.push_back(framework::FRAME_INFO({ 480, 440, 560, 550 }, 0.1f));
	frame_MoveFront.push_back(framework::FRAME_INFO({ 560, 440, 640, 550 }, 0.1f));

	std::vector<framework::FRAME_INFO> frame_MoveSide;
	frame_MoveSide.push_back(framework::FRAME_INFO({ 0,550, 80, 660 }, 0.1f));
	frame_MoveSide.push_back(framework::FRAME_INFO({ 80,550, 160, 660 }, 0.1f));
	frame_MoveSide.push_back(framework::FRAME_INFO({ 160,550, 240, 660 }, 0.1f));
	frame_MoveSide.push_back(framework::FRAME_INFO({ 240,550, 320, 660 }, 0.1f));
	frame_MoveSide.push_back(framework::FRAME_INFO({ 320,550, 400, 660 }, 0.1f));
	frame_MoveSide.push_back(framework::FRAME_INFO({ 400,550, 480, 660 }, 0.1f));
	frame_MoveSide.push_back(framework::FRAME_INFO({ 480,550, 560, 660 }, 0.1f));
	frame_MoveSide.push_back(framework::FRAME_INFO({ 560,550, 640, 660 }, 0.1f));

	std::vector<framework::FRAME_INFO> frame_Stun;
	frame_Stun.push_back(framework::FRAME_INFO({ 0,660, 80, 780 }, 0.1f));
	frame_Stun.push_back(framework::FRAME_INFO({ 80,660, 160, 780 }, 0.1f));
	frame_Stun.push_back(framework::FRAME_INFO({ 160,660, 240, 780 }, 0.1f));
	frame_Stun.push_back(framework::FRAME_INFO({ 240,660, 320, 780 }, 0.1f));

	if (m_name == L"Player1")
	{
		m_pAnimComponent->SetAnimationAsset(L"../Resource/red_racoon_sheet.png", L"IDLE_BACK", frame_IdleBack);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/red_racoon_sheet.png", L"IDLE_FRONT", frame_IdleFront);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/red_racoon_sheet.png", L"IDLE_SIDE", frame_IdleSide);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/red_racoon_sheet.png", L"MOVE_BACK", frame_MoveBack);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/red_racoon_sheet.png", L"MOVE_FRONT", frame_MoveFront);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/red_racoon_sheet.png", L"MOVE_SIDE", frame_MoveSide);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/red_racoon_sheet.png", L"STUN", frame_Stun);
	}
	else if (m_name == L"Player2")
	{
		m_pAnimComponent->SetAnimationAsset(L"../Resource/blue_racoon_sheet.png", L"IDLE_BACK", frame_IdleBack);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/blue_racoon_sheet.png", L"IDLE_FRONT", frame_IdleFront);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/blue_racoon_sheet.png", L"IDLE_SIDE", frame_IdleSide);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/blue_racoon_sheet.png", L"MOVE_BACK", frame_MoveBack);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/blue_racoon_sheet.png", L"MOVE_FRONT", frame_MoveFront);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/blue_racoon_sheet.png", L"MOVE_SIDE", frame_MoveSide);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/blue_racoon_sheet.png", L"STUN", frame_Stun);
	}
	else if (m_name == L"Player3")
	{
		m_pAnimComponent->SetAnimationAsset(L"../Resource/yellow_racoon_sheet.png", L"IDLE_BACK", frame_IdleBack);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/yellow_racoon_sheet.png", L"IDLE_FRONT", frame_IdleFront);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/yellow_racoon_sheet.png", L"IDLE_SIDE", frame_IdleSide);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/yellow_racoon_sheet.png", L"MOVE_BACK", frame_MoveBack);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/yellow_racoon_sheet.png", L"MOVE_FRONT", frame_MoveFront);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/yellow_racoon_sheet.png", L"MOVE_SIDE", frame_MoveSide);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/yellow_racoon_sheet.png", L"STUN", frame_Stun);
	}
	else if (m_name == L"Player4")
	{
		m_pAnimComponent->SetAnimationAsset(L"../Resource/green_racoon_sheet.png", L"IDLE_BACK", frame_IdleBack);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/green_racoon_sheet.png", L"IDLE_FRONT", frame_IdleFront);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/green_racoon_sheet.png", L"IDLE_SIDE", frame_IdleSide);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/green_racoon_sheet.png", L"MOVE_BACK", frame_MoveBack);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/green_racoon_sheet.png", L"MOVE_FRONT", frame_MoveFront);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/green_racoon_sheet.png", L"MOVE_SIDE", frame_MoveSide);
		m_pAnimComponent->SetAnimationAsset(L"../Resource/green_racoon_sheet.png", L"STUN", frame_Stun);
	}
}

// OnTriggerEnter에서 상대 Object가 ItemBox인지 확인하고 호출
bool PlayerObject::GetRandomItem(eItemBoxType itemBoxType)
{
	TestWorld* testWorld = dynamic_cast<TestWorld*>(m_pOwnerWorld);
	InGameWorld* inGameWorld = dynamic_cast<InGameWorld*>(m_pOwnerWorld);

	assert(testWorld || inGameWorld);

	if(m_OwnedItem[static_cast<UINT>(itemBoxType)] == eItemType::NOTHING)
	{
		m_OwnedItem[static_cast<UINT>(itemBoxType)] = inGameWorld->GetRandomItem(itemBoxType);
		//m_OwnedItem[static_cast<UINT>(itemBoxType)] = testWorld->GetRandomItem(itemBoxType);
		return true;
	}
	else
	{
		return false;
	}
}

void PlayerObject::CreateInstance(eItemType itemType)
{
	m_pCreatedItem = nullptr;

	switch(itemType)
	{
	// THROW
	case eItemType::PunchItem :
		m_pCreatedItem = m_pOwnerWorld->CreateGameObject<PunchItem>(L"PunchItem", GROUP_TYPE::ITEM);
		break;
	case eItemType::SnowItem :
		m_pCreatedItem = m_pOwnerWorld->CreateGameObject<SnowItem>(L"SnowItem", GROUP_TYPE::ITEM);
		break;
	case eItemType::BottleItem:
		m_pCreatedItem = m_pOwnerWorld->CreateGameObject<BottleItem>(L"BottleItem", GROUP_TYPE::ITEM);
		break;

	// INSTALLATION
	case eItemType::TrapItem:
		m_pCreatedItem = m_pOwnerWorld->CreateGameObject<TrapItem>(L"TrapItem", GROUP_TYPE::ITEM);
		break;

	// REINFORCED
	case eItemType::ShoeItem:
		m_pCreatedItem = m_pOwnerWorld->CreateGameObject<ShoeItem>(L"ShoeItem", GROUP_TYPE::ITEM);
		break;
	case eItemType::WaveItem:
		m_pCreatedItem = m_pOwnerWorld->CreateGameObject<WaveItem>(L"WaveItem", GROUP_TYPE::ITEM);
		break;

	default :
		return;
	}

	m_pCreatedItem->SetOwnerObj(this);
	m_pCreatedItem->SetOwnerPlayer(this);
	m_pCreatedItem->Initialize();
}

void PlayerObject::UseThrowItem()
{
	CreateInstance(m_OwnedItem[static_cast<UINT>(eItemBoxType::THROW)]);
	m_OwnedItem[static_cast<UINT>(eItemBoxType::THROW)] = eItemType::NOTHING;	// test
	printf("UseThrowItem");
}

void PlayerObject::UseInstallationItem()
{
	CreateInstance(m_OwnedItem[static_cast<UINT>(eItemBoxType::INSTALLATION)]);
	m_OwnedItem[static_cast<UINT>(eItemBoxType::INSTALLATION)] = eItemType::NOTHING;	// test
	printf("UseInstallationItem");
}

void PlayerObject::UseReinforcedItem()
{
	CreateInstance(m_OwnedItem[static_cast<UINT>(eItemBoxType::REINFORCED)]);
	m_OwnedItem[static_cast<UINT>(eItemBoxType::REINFORCED)] = eItemType::NOTHING;
	printf("UseReinforcedItem");
}
