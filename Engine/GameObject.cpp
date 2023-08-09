#include "pch.h"
#include "GameObject.h"

#include "CommonApp.h"
#include "RenderComponent.h"

GameObject::~GameObject()
{
	for (const auto& component : m_OwnedComponent)
	{
		delete component;
	}
	m_OwnedComponent.clear();
}

bool GameObject::Initialize()
{
	// 게임 오브젝트가 가지고 있는 모든 컴포넌트를 순회
	for (const auto& component : m_OwnedComponent)
	{
		// SceneComponent라면 Initialize()를 호출한다
		SceneComponent* sceneComponent = dynamic_cast<SceneComponent*>(component);
		if (sceneComponent != nullptr)
		{
			bool res = sceneComponent->Initialize();
			assert(res);
		}
	}

	return true;
}

void GameObject::Update(const float deltaTime)
{
	for (const auto& component : m_OwnedComponent)
	{
		component->Update(deltaTime);
	}
}

void GameObject::Render()
{
	// RenderComponent로 타입캐스팅이 되는(직/간접적으로 상속받은) 컴포넌트만 렌더링한다.
	for (auto component : m_OwnedComponent)
	{
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component);
#ifdef FRAMEWORK_DEBUG
		// todo : 콜라이더 렌더링 예외처리 추가
#endif
		if (renderComponent != nullptr)
		{
			renderComponent->Render(CommonApp::m_pInstance->GetRenderTarget());
		}
	}
}

Component* GameObject::GetComponent(const std::wstring name) const
{
	for (const auto& component : m_OwnedComponent)
	{
		if (component->GetName() == name)
			return component;
	}
	return nullptr;
}