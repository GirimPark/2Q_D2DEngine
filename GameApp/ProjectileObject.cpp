#include "framework.h"
#include "ProjectileObject.h"

#include "../Engine/BoxComponent.h"
#include "../Engine/BoxCollider2D.h"
#include "../Engine/EventManager.h"
#include "../Engine/PlayerMovement.h"

ProjectileObject::~ProjectileObject()
{
}

bool ProjectileObject::Initialize()
{
	/// BoxComponent
	m_pBoxComponent = CreateComponent<BoxComponent>(L"BoxComponent");
	m_pBoxComponent->SetExtend(10.f, 10.f);
	m_pBoxComponent->SetColor(D2D1::ColorF::White);
	m_pBoxComponent->SetRelativeLocation(m_Position.x, m_Position.y);
	SetRootComponent(m_pBoxComponent);

	/// BoxCollider2D
	m_pBoxCollider2D = CreateComponent<BoxCollider2D>(L"BoxCollider2D");
	m_pBoxCollider2D->SetCollisionType(COLLISION_TPYE::TRIGGER);
	m_pBoxCollider2D->SetExtend(5.f, 5.f);
	m_pBoxCollider2D->AttachToComponent(m_pBoxComponent);

	const bool res = GameObject::Initialize();
	assert(res);

	return true;
}

void ProjectileObject::Update(const float deltaTime)
{
	m_LifeTime += deltaTime;

	if (m_LifeTime >= m_MaxLifeTime)
	{
		// World의 m_GameObjects에서 제거해줘야 한다
		m_LifeTime = 0.f;
		EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::ITEM, this);
		return;
	}

	// m_Direction과 m_Speed를 이용하여 이동
	m_Velocity = m_Direction * m_Speed;

	// 플레이어 이동
	GetRootComponent()->AddRelativeLocation(m_Velocity * deltaTime);

	GameObject::Update(deltaTime);
}

void ProjectileObject::OnCollisionEnter(Collider2D* otherCollision)
{

}

void ProjectileObject::OnCollisionStay(Collider2D* otherCollision)
{

}

void ProjectileObject::OnCollisionExit(Collider2D* otherCollision)
{

}

void ProjectileObject::OnTriggerEnter(Collider2D* otherCollision)
{
	if(otherCollision->GetOwner()->GetComponent<PlayerMovement>())
	{
		// this 총알 삭제
		EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::ITEM, this);

		// Exit 처리 해주기
		this->GetComponent<BoxCollider2D>()->TurnOff_IsTrigger(otherCollision);
		otherCollision->OnTriggerExit(this->GetComponent<BoxCollider2D>());

		return;
	}
}

void ProjectileObject::OnTriggerStay(Collider2D* otherCollision)
{

}

void ProjectileObject::OnTriggerExit(Collider2D* otherCollision)
{

}
