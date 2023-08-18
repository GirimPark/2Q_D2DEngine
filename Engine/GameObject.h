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
/// GameObject���� ����
/// ���ӿ�����Ʈ ��ü�δ� �ƹ��͵� ������ �ʴ´�.
/// ������Ʈ �� ��ǥ ������Ʈ�� �����Ͽ� �ش� ������Ʈ�� ��ġ���� ��ǥ��ġ������ ������.
/// �ν��Ͻ�ȭ �� ������Ʈ�� IAnimationNotify �� �������̽��� ��ӹ޾� ������ ������ �Ѵ�.
/// </summary>
class GameObject
	: public Object
{
private:
	// ���� ��ü�� Ʈ�������� �������� �ʴ´�.
	// ���� �� �ϳ��� ��ǥ ��ġ������ �����ϰ�, ���� ������ �θ��ڽ� ���踦 �������ϰ� �Ѵ�.
	std::vector<Component*> m_OwnedComponent;
	// m_pRootComponent�� m_OwnedComponent �� �ϳ��� ����, ��ǥ ��ġ��
	SceneComponent* m_pRootComponent = nullptr;

	// (�˾�����������)�˾��� �ƴ���
	bool m_bPopUpState = false;

	bool m_bActiveObject = true;
	bool m_bIsDead = false;

protected:
	D2D1::ColorF m_CullingRectColor = D2D1::ColorF::Green;
	std::wstring m_name;

	// ������Ʈ ���� �θ�/�ڽ� ����
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
		// T ������Ʈ�� ã�Ƽ� ��ȯ
		for (Component* component : m_OwnedComponent)
		{
			// T ������Ʈ�� ��ӹ��� ������Ʈ�� component�� ������� ��� component�� T*���� ĳ���� �ؼ� ��ȯ
			// Collider2D -> BoxCollider2D / CircleCollider2D
			T* castedCom = dynamic_cast<T*>(component);
			if (castedCom != nullptr)
				return castedCom;
		}

		// T ������Ʈ�� ������ nullptr
		return nullptr;
	}

	template <typename T>
	T* GetComponent(const std::wstring& name) const
	{
		// T ������Ʈ�� ã�Ƽ� ��ȯ
		for (Component* component : m_OwnedComponent)
		{
			// T ������Ʈ�� ��ӹ��� ������Ʈ�� component�� ������� ��� component�� T*���� ĳ���� �ؼ� ��ȯ
			// Collider2D -> BoxCollider2D / CircleCollider2D
			T* castedCom = dynamic_cast<T*>(component);
			if (castedCom != nullptr && castedCom->GetName() == name)
				return castedCom;
		}

		// T ������Ʈ�� ������ nullptr
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