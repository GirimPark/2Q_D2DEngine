#pragma once
#include <vector>
#include <cassert>
#include "Object.h"
#include "AABB.h"
#include "Component.h"

class SceneComponent;

/*---------------------------------------------------------------------------------
GameObject들의 원형
게임오브젝트 자체로는 아무것도 가지지 않는다.
컴포넌트 중 대표 컴포넌트를 지정하여 해당 컴포넌트의 위치값을 대표위치값으로 가진다.
인스턴스화 된 오브젝트는 IAnimationNotify 등 인터페이스를 상속받아 리스너 역할을 한다.
----------------------------------------------------------------------------------*/
class GameObject
	: public Object
{
private:
	// 벡터 자체가 트리구조를 가지지는 않는다.
	// 벡터 중 하나를 대표 위치값으로 설정하고, 벡터 내에서 부모자식 관계를 포인팅하게 한다.
	std::vector<Component*> m_OwnedComponent;
	//std::map<std::wstring, Component*> m_OwndComponent;
	// m_pRootComponent는 m_OwnedComponent 중 하나로 설정, 대표 위치값
	SceneComponent* m_pRootComponent = nullptr;

protected:
	D2D1::ColorF m_CullingRectColor = D2D1::ColorF::White;
	AABB m_ObjAABB;
	std::wstring m_name;
	// 오브젝트 간의 부모/자식 관계
	GameObject* m_pOwnerObj = nullptr;

public:
	virtual ~GameObject();

public:
	void SetRootComponent(SceneComponent* rootComponent) { m_pRootComponent = rootComponent; }
	SceneComponent*& GetRootComponent() { return m_pRootComponent; }
	Component* GetComponent(std::wstring name);

	AABB& GetAABB() { return m_ObjAABB; }

	std::wstring GetName() { return m_name; }
	void SetName(std::wstring name) { m_name = name; }

	void SetOwnerObj(GameObject* _pOwnerObj) { m_pOwnerObj = _pOwnerObj; }
	GameObject* GetOwnerObj() { return m_pOwnerObj; }

private:
	void CalAABB();
	void RenderAABB();

public:
	virtual bool Initialize();
	virtual void Update();
	virtual void Render();

public:
	template <typename T>
	T* CreateComponent(std::wstring name)
	{
		T* component = new T;

		Component* castedComponent = dynamic_cast<Component*>(component);
		assert(castedComponent != nullptr);

		castedComponent->SetName(name);
		castedComponent->SetOwner(this);
		m_OwnedComponent.push_back(castedComponent);

		return component;
	}
};

