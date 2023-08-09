#include "framework.h"
#include "DemoObject.h"

#include "GameApp.h"

#include "../Engine/BoxComponent.h"

bool DemoObject::Initialize()
{
	m_pBoxComponent1 = CreateComponent<BoxComponent>(L"Sun");
	m_pBoxComponent1->SetWidth(50.f);
	m_pBoxComponent1->SetHeight(50.f);
	m_pBoxComponent1->SetColor(D2D1::ColorF::Red);
	m_pBoxComponent1->SetRelativeLocation(ScreenWidth/2.f, ScreenHeight/2.f);
	SetRootComponent(m_pBoxComponent1);

	m_pBoxComponent2 = CreateComponent<BoxComponent>(L"Earth");
	m_pBoxComponent2->SetWidth(30.f);
	m_pBoxComponent2->SetHeight(30.f);
	m_pBoxComponent2->SetColor(D2D1::ColorF::Green);
	m_pBoxComponent2->SetRelativeLocation(150.f, 0.f);
	m_pBoxComponent2->AttachToComponent(m_pBoxComponent1);

	m_pBoxComponent3 = CreateComponent<BoxComponent>(L"Moon");
	m_pBoxComponent3->SetWidth(20.f);
	m_pBoxComponent3->SetHeight(20.f);
	m_pBoxComponent3->SetColor(D2D1::ColorF::Yellow);
	m_pBoxComponent3->SetRelativeLocation(60.f, 0.f);
	m_pBoxComponent3->AttachToComponent(m_pBoxComponent2);

	__super::Initialize();

	return true;
}

void DemoObject::Update(const float deltaTime)
{
	m_pBoxComponent1->AddRelativeRotation(30.f * deltaTime);
	m_pBoxComponent2->AddRelativeRotation(70.f * deltaTime);
	m_pBoxComponent3->AddRelativeRotation(100.f * deltaTime);

	__super::Update(deltaTime);
}