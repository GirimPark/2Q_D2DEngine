#include "pch.h"
#include "CommonApp.h"
#include "RenderComponent.h"
#include "GameObject.h"

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
	for (const auto& component : m_OwnedComponent)
	{
		SceneComponent* sceneComponent = dynamic_cast<SceneComponent*>(component);
		if (sceneComponent != nullptr)
		{
			assert(sceneComponent->Initialize());
		}
	}

	return true;
}

void GameObject::Update()
{
	for (const auto& component : m_OwnedComponent)
	{
		component->Update();
	}

	CalAABB();
}

void GameObject::Render()
{
	// RenderComponent로 타입캐스팅이 되는(직/간접적으로 상속받은) 컴포넌트만 렌더링한다.
	for (auto component : m_OwnedComponent)
	{
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component);
		if (renderComponent != nullptr)
		{
			renderComponent->Render(CommonApp::m_pInstance->getRenderTarget());
		}
	}

#ifdef DEBUG
	RenderAABB();
#endif
}

void GameObject::CalAABB()
{
	m_ObjAABB.m_Center = m_pRootComponent->GetWorldLocation();

	// 카메라 오브젝트인 경우, CullingRect를 viewPort로 고정
	CameraComponent* cameraComponent = dynamic_cast<CameraComponent*>(m_pRootComponent);
	if (cameraComponent != nullptr)
	{
		m_ObjAABB = cameraComponent->GetViewPort();
		return;
	}

	float tempExtend = 0;
	for (auto component : m_OwnedComponent)
	{
		RenderComponent* renderComponent = dynamic_cast<RenderComponent*>(component);
		if (renderComponent != nullptr)
		{
			framework::Rect boundingBox = renderComponent->GetComponentAABB()->m_CullingBox;
			// 네 점의 위치를 비교해서 CullingRect 결정

			if (tempExtend < m_ObjAABB.m_Center.x - boundingBox.left)
				tempExtend = m_ObjAABB.m_Center.x - boundingBox.left;
			if (tempExtend < m_ObjAABB.m_Center.y - boundingBox.top)
				tempExtend = m_ObjAABB.m_Center.y - boundingBox.top;
			if (tempExtend < boundingBox.right - m_ObjAABB.m_Center.x)
				tempExtend = boundingBox.right - m_ObjAABB.m_Center.x;
			if (tempExtend < boundingBox.bottom - m_ObjAABB.m_Center.y)
				tempExtend = boundingBox.bottom - m_ObjAABB.m_Center.y;

			m_ObjAABB.m_Extend = tempExtend;

			m_ObjAABB.CalCullingBox();
		}
	}
}

Component* GameObject::GetComponent(std::wstring name)
{
	for (const auto& component : m_OwnedComponent)
	{
		if (component->GetName() == name)
			return component;
	}
	return nullptr;
}

void GameObject::RenderAABB()
{
	CommonApp::m_pInstance->getBrush()->SetColor(m_CullingRectColor);

	if (this->GetName() == L"CameraObject")
	{
		CommonApp::m_pInstance->getRenderTarget()->SetTransform(
			D2D1::Matrix3x2F::Translation(ScreenWidth / 2.f, ScreenHeight / 2.f));
	}
	else
	{
		CommonApp::m_pInstance->getRenderTarget()->SetTransform(
			D2D1::Matrix3x2F::Translation(m_pRootComponent->GetFinalLocation().x, m_pRootComponent->GetFinalLocation().y));
	}

	CommonApp::m_pInstance->getRenderTarget()->DrawRectangle(
		{ -m_ObjAABB.m_Extend, -m_ObjAABB.m_Extend, m_ObjAABB.m_Extend, m_ObjAABB.m_Extend },
		CommonApp::m_pInstance->getBrush(),
		2.f);

	CommonApp::m_pInstance->getRenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity());
}