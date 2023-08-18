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
/// �÷��̾� ������Ʈ
///	1P ~ 4P ��� ������ Ŭ������ ���
/// </summary>
class PlayerObject final
	: public GameObject
	, public EventListener
{
private:
	// ItemType�� ���ؼ� ���� ����ϴ� ������ �ν��Ͻ� �������ֱ�
	eItemType m_OwnedItem[static_cast<UINT>(eItemBoxType::END_ITEMBOX)] = {};	// ��ô��, ��ȭ��, ��ġ�� - ������, �����
	UINT m_PlayerNumber = 0;
	int m_HP = 5;
	int m_Money = 0;

	AnimationComponent* m_pAnimComponent = nullptr;
	PlayerMovement* m_pMovementComponent = nullptr;
	FSMComponent* m_pFSMComponent = nullptr;
	FSM* m_pPlayerFSM = nullptr;
	DirectionComponent* m_pDirectionComponent = nullptr;
	BoxCollider2D* m_pBoxColliderFull = nullptr;
	BoxCollider2D* m_pBoxColliderPart = nullptr;	// ��, ���� ������ �� ������ �ݶ��̴�

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