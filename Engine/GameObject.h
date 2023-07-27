#pragma once
#include <vector>
#include <cassert>
#include "Object.h"
#include "AABB.h"
#include "Component.h"

class SceneComponent;

/*---------------------------------------------------------------------------------
GameObject���� ����
���ӿ�����Ʈ ��ü�δ� �ƹ��͵� ������ �ʴ´�.
������Ʈ �� ��ǥ ������Ʈ�� �����Ͽ� �ش� ������Ʈ�� ��ġ���� ��ǥ��ġ������ ������.
�ν��Ͻ�ȭ �� ������Ʈ�� IAnimationNotify �� �������̽��� ��ӹ޾� ������ ������ �Ѵ�.
----------------------------------------------------------------------------------*/
class GameObject
	: public Object
{
private:
	// ���� ��ü�� Ʈ�������� �������� �ʴ´�.
	// ���� �� �ϳ��� ��ǥ ��ġ������ �����ϰ�, ���� ������ �θ��ڽ� ���踦 �������ϰ� �Ѵ�.
	std::vector<Component*> m_OwnedComponent;
	//std::map<std::wstring, Component*> m_OwndComponent;
	// m_pRootComponent�� m_OwnedComponent �� �ϳ��� ����, ��ǥ ��ġ��
	SceneComponent* m_pRootComponent = nullptr;

protected:
	D2D1::ColorF m_CullingRectColor = D2D1::ColorF::White;
	AABB m_ObjAABB;
	std::wstring m_name;
	// ������Ʈ ���� �θ�/�ڽ� ����
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

