#include "framework.h"
#include "MoneyObject.h"

#include "../Engine/BoxCollider2D.h"
#include "../Engine/EventManager.h"
#include "../Engine/TextureComponent.h"
#include "../Engine/World.h"

bool MoneyObject::Initialize()
{
	m_pTextureComponent = CreateComponent<TextureComponent>(L"MoneyTexture");
	m_pTextureComponent->SetTextureAsset(L"../Resource/MoneyObject.png", L"MoneyObject");
	SetRootComponent(m_pTextureComponent);

	m_pCollider = CreateComponent<BoxCollider2D>(L"BoxCollider2D");
	m_pCollider->SetExtend(30.f, 30.f);
	m_pCollider->SetCollisionType(COLLISION_TPYE::TRIGGER);
	m_pCollider->AttachToComponent(m_pTextureComponent);

	bool res = __super::Initialize();
	assert(res);

	return true;
}

void MoneyObject::Update(const float deltaTime)
{
	if(this->m_MoneyType == eMoneyType::OWNED)
	{
		EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::MONEY, this);
		return;
	}

	__super::Update(deltaTime);
}