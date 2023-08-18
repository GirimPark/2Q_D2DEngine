#pragma once
#include "../Engine/GameObject.h"

class TextureComponent;
class BoxCollider2D;

enum eMoneyType
{
	SPAWNED,
	OWNED,
	DROPED,
};

class MoneyObject
	: public GameObject
{
private:
	eMoneyType m_MoneyType = eMoneyType::SPAWNED;
	TextureComponent* m_pTextureComponent = nullptr;
	BoxCollider2D* m_pCollider = nullptr;

public:
	void SetMoneyType(eMoneyType moneyType) { m_MoneyType = moneyType; }
	eMoneyType GetMoneyType() { return m_MoneyType; }

public:
	bool Initialize() final;
	void Update(const float deltaTime) final;
};

