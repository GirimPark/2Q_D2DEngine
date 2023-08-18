#include "framework.h"
#include "ShoeItem.h"

#include "PlayerObject.h"

#include "../Engine/PlayerMovement.h"
#include "../Engine/EventManager.h"
#include "../Engine/World.h"

bool ShoeItem::Initialize()
{
	PlayerMovement* playerMovement = m_pOwnerPlayer->GetComponent<PlayerMovement>();
	// 이동속도 두배로 만들기
	playerMovement->SetPlayerSpeedDouble();
	this->SetItemType(eItemType::REINFORCED_START);
	return true;
}

void ShoeItem::Update(const float deltaTime)
{
	static float elapsedTime = 0.f;

	elapsedTime += deltaTime;

	if(elapsedTime > 2.f)
	{
		PlayerMovement* playerMovement = m_pOwnerPlayer->GetComponent<PlayerMovement>();
		// 이동속도 원래대로
		playerMovement->SetPlayerSpeedTurnBack();
		// 이제 끝남
		this->SetItemType(eItemType::REINFORCED_END);
		elapsedTime = 0;
		EventManager::GetInstance()->SendEvent(eEventType::DeleteGameObject, GROUP_TYPE::ITEM, this);
	}
}