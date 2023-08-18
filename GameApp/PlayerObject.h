#pragma once

#include "../Engine/GameObject.h"
#include "../Engine/EventListener.h"

#include "ItemBoxObject.h"
#include "ItemObject.h"

class ItemObject;
class AnimationComponent;
class PlayerMovement;
class FSMComponent;
class FSM;
class DirectionComponent;
class BoxCollider2D;

enum class eItemBoxType;

/// <summary>
/// 플레이어 오브젝트
///	1P ~ 4P 모두 동일한 클래스를 사용
/// </summary>
class PlayerObject final
	: public GameObject
	, public EventListener
{
private:
	// ItemType을 통해서 실제 사용하는 시점에 인스턴스 생성해주기
	eItemType m_OwnedItem[static_cast<UINT>(eItemBoxType::END_ITEMBOX)] = {};	// 투척형, 강화형, 설치형 - 보유중, 사용중
	UINT m_PlayerNumber = 0;
	int m_HP = 5;
	int m_Money = 0;

	AnimationComponent* m_pAnimComponent = nullptr;
	PlayerMovement* m_pMovementComponent = nullptr;
	FSMComponent* m_pFSMComponent = nullptr;
	FSM* m_pPlayerFSM = nullptr;
	DirectionComponent* m_pDirectionComponent = nullptr;
	BoxCollider2D* m_pBoxColliderFull = nullptr;
	BoxCollider2D* m_pBoxColliderPart = nullptr;	// 덫, 오일 아이템 등 감지용 콜라이더

	ItemObject* m_pCreatedItem = nullptr;

public:
	~PlayerObject() final;

public:
	bool Initialize() final;
	void Update(const float deltaTime) final;

	void OnCollisionEnter(Collider2D* otherCollision) final;
	void OnCollisionStay(Collider2D* otherCollision) final;
	void OnCollisionExit(Collider2D* otherCollision) final;

	void OnTriggerEnter(Collider2D* otherCollision) final;
	void OnTriggerStay(Collider2D* otherCollision) final;
	void OnTriggerExit(Collider2D* otherCollision) final;

public:
	void HandleEvent(Event* event) final;

public:
	void AttachFSM(FSM* fsm);

private:
	void InitAnimationAsset();

	bool GetRandomItem(eItemBoxType itemBoxType);

	void CreateInstance(eItemType itemType);
	void UseThrowItem();
	void UseInstallationItem();
	void UseReinforcedItem();
};