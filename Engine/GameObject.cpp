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
	// ���� ������Ʈ�� ������ �ִ� ��� ������Ʈ�� ��ȸ
	for (const auto& component : m_OwnedComponent)
	{
		// SceneComponent��� Initialize()�� ȣ���Ѵ�
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
	// RenderComponent�� Ÿ��ĳ������ �Ǵ�(��/���������� ��ӹ���) ������Ʈ�� �������Ѵ�.
	for (auto component : m_OwnedComponent)
	{
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component);
#ifdef FRAMEWORK_DEBUG
		// todo : �ݶ��̴� ������ ����ó�� �߰�
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