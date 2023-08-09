#include "framework.h"
#include "BoxObject.h"

#include "../Engine/BoxComponent.h"

bool BoxObject::Initialize()
{
	 m_pBoxComponent = CreateComponent<BoxComponent>(L"BoxComponent");
	 m_pBoxComponent->SetWidth(50.f);
	 m_pBoxComponent->SetHeight(50.f);
	 m_pBoxComponent->SetColor(D2D1::ColorF::LightPink);
	 m_pBoxComponent->SetRelativeLocation(ScreenWidth / 2.f + 200.f, ScreenHeight / 2.f + 200.f);
	 SetRootComponent(m_pBoxComponent);

	__super::Initialize();

	return true;
}

void BoxObject::Update(const float deltaTime)
{


	__super::Update(deltaTime);
}