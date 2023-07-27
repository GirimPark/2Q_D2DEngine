#pragma once
#include "Object.h"

class GameObject;

/*----------------------------------------------------
���� ������ Component
Component�� ���� ������ �θ� ������Ʈ, �̸��� ������.
�뷫���� Component ������ �Ʒ��� ����.
Component
  -SceneComponent
    -CameraComponent
    -RenderComponent
      -RenderableComponents...
  -MoveComponent
  -FSMComponent
-----------------------------------------------------*/
class Component
	: public Object
{
protected:
	GameObject* m_pOwner;
	std::wstring m_name;

public:
	void SetOwner(GameObject* pOwner) { m_pOwner = pOwner; }
	GameObject* GetOwner() { return m_pOwner; }

	void SetName(std::wstring name) { m_name = name; }
	std::wstring GetName() { return m_name; }

public:
	virtual void Update() abstract;
};

