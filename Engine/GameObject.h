#pragma once

#include "Object.h"
#include "Component.h"

#include <vector>
#include <cassert>

class UIObject;
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
	// m_pRootComponent�� m_OwnedComponent �� �ϳ��� ����, ��ǥ ��ġ��
	SceneComponent* m_pRootComponent = nullptr;

protected:
	D2D1::ColorF m_CullingRectColor = D2D1::ColorF::Green;
	std::wstring m_name;
	// ������Ʈ ���� �θ�/�ڽ� ����
	GameObject* m_pOwnerObj = nullptr;

public:
	virtual ~GameObject();

public:
	void SetRootComponent(SceneComponent* rootComponent) { m_pRootComponent = rootComponent; }
	SceneComponent* GetRootComponent() const { return m_pRootComponent; }
	Component* GetComponent (const std::wstring name) const;

	std::wstring GetName() const { return m_name; }
	void SetName(const std::wstring name) { m_name = name; }

	void SetOwnerObj(GameObject* _pOwnerObj) { m_pOwnerObj = _pOwnerObj; }
	GameObject* GetOwnerObj() const { return m_pOwnerObj; }

public:
	virtual bool Initialize();
	virtual void Update(const float deltaTime);
	virtual void Render();

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
};

