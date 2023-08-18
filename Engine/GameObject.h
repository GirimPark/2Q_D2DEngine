#pragma once

#include "Object.h"

#include <vector>
#include <cassert>

#include "SceneComponent.h"

enum class GROUP_TYPE
{
	PLAYER = 0,
	ITEM,
	MONEY,
	ITEMBOX,
	ENVIRONMENT,
	UI,
	POPUPUI,
	OBSTACLE,
	SPAWNER,

	END
};

class Collider2D;
class UIObject;
class SceneComponent;
class World;

/// <summary>
/// GameObject들의 원형
/// 게임오브젝트 자체로는 아무것도 가지지 않는다.
/// 컴포넌트 중 대표 컴포넌트를 지정하여 해당 컴포넌트의 위치값을 대표위치값으로 가진다.
/// 인스턴스화 된 오브젝트는 IAnimationNotify 등 인터페이스를 상속받아 리스너 역할을 한다.
/// </summary>
class GameObject
	: public Object
{
private:
	// 벡터 자체가 트리구조를 가지지는 않는다.
	// 벡터 중 하나를 대표 위치값으로 설정하고, 벡터 내에서 부모자식 관계를 포인팅하게 한다.
	std::vector<Component*> m_OwnedComponent;
	// m_pRootComponent는 m_OwnedComponent 중 하나로 설정, 대표 위치값
	SceneComponent* m_pRootComponent = nullptr;

	// (팝업유아이전용)팝업이 됐는지
	bool m_bPopUpState = false;

	bool m_bActiveObject = true;
	bool m_bIsDead = false;

protected:
	D2D1::ColorF m_CullingRectColor = D2D1::ColorF::Green;
	std::wstring m_name;

	// 오브젝트 간의 부모/자식 관계
	GameObject* m_pOwnerObj = nullptr;
	World* m_pOwnerWorld = nullptr;

public:
	virtual ~GameObject();

public:
	void SetRootComponent(SceneComponent* rootComponent) { m_pRootComponent = rootComponent; }
	SceneComponent* GetRootComponent() const { return m_pRootComponent; }
	Component* GetComponent (const std::wstring& name) const;
	std::vector<Component*> GetComponents(const std::wstring& name) const;

	std::wstring GetName() const { return m_name; }
	void SetName(const std::wstring name) { m_name = name; }

	void SetOwnerObj(GameObject* _pOwnerObj) { m_pOwnerObj = _pOwnerObj; }
	GameObject* GetOwnerObj() const { return m_pOwnerObj; }

	void SetOwnerWorld(World* pOwnerWorld) { m_pOwnerWorld = pOwnerWorld; }
	World* GetOwnerWorld() const { return m_pOwnerWorld; }

	void SetLocation(const float x, const float y) const;
	framework::Vector2D GetLocation() const { return m_pRootComponent->GetWorldLocation(); };

	void SetActiveObj(bool activeObject) { m_bActiveObject = activeObject; }
	bool IsObjActive() const { return m_bActiveObject; }

	bool GetPopUpState() { return m_bPopUpState; }
	void SetPopUpState(bool popupState) { m_bPopUpState = popupState; }

	bool IsDead() const { return m_bIsDead; }
	void RevivePlayer() { m_bIsDead = false; }
	void KillPlayer() { m_bIsDead = true; }

public:
	virtual bool Initialize();
	virtual void Update(const float deltaTime);
	virtual void Render();

public:
	virtual void OnCollisionEnter(Collider2D* otherCollision) {}
	virtual void OnCollisionStay(Collider2D* otherCollision) {}
	virtual void OnCollisionExit(Collider2D* otherCollision) {}

	virtual void OnTriggerEnter(Collider2D* otherCollision) {}
	virtual void OnTriggerStay(Collider2D* otherCollision) {}
	virtual void OnTriggerExit(Collider2D* otherCollision) {}

public:
	template <typename T>
	T* CreateComponent(std::wstring name)
	{
		T* component = new T;

		Component* castedComponent = dynamic_cast<Component*>(component);
		assert(castedComponent);

		castedComponent->SetName(name);
		castedComponent->SetOwner(this);
		m_OwnedComponent.push_back(castedComponent);

		return component;
	}

	template <typename T>
	T* GetComponent() const
	{
		// T 컴포넌트를 찾아서 반환
		for (Component* component : m_OwnedComponent)
		{
			// T 컴포넌트를 상속받은 컴포넌트가 component에 들어있을 경우 component을 T*으로 캐스팅 해서 반환
			// Collider2D -> BoxCollider2D / CircleCollider2D
			T* castedCom = dynamic_cast<T*>(component);
			if (castedCom != nullptr)
				return castedCom;
		}

		// T 컴포넌트가 없으면 nullptr
		return nullptr;
	}

	template <typename T>
	T* GetComponent(const std::wstring& name) const
	{
		// T 컴포넌트를 찾아서 반환
		for (Component* component : m_OwnedComponent)
		{
			// T 컴포넌트를 상속받은 컴포넌트가 component에 들어있을 경우 component을 T*으로 캐스팅 해서 반환
			// Collider2D -> BoxCollider2D / CircleCollider2D
			T* castedCom = dynamic_cast<T*>(component);
			if (castedCom != nullptr && castedCom->GetName() == name)
				return castedCom;
		}

		// T 컴포넌트가 없으면 nullptr
		return nullptr;
	}

	template <typename T>
	std::vector<T*> GetComponents() const
	{
		std::vector<T*> components;
		for (const auto& component : m_OwnedComponent)
		{
			T* castedCom = dynamic_cast<T*>(component);
			if (castedCom != nullptr)
				components.push_back(castedCom);
		}

		return components;
	}

	template <typename T>
	std::vector<Component*> GetComponents(const std::wstring& name) const
	{
		std::vector<Component*> components;
		for (const auto& component : m_OwnedComponent)
		{
			T* castedCom = dynamic_cast<T*>(component);
			if (castedCom != nullptr && castedCom->GetName() == name)
				components.push_back(castedCom);
		}

		return components;
	}
};