#pragma once
#include "Object.h"

class GameObject;

/*----------------------------------------------------
가장 상위의 Component
Component의 공통 정보인 부모 오브젝트, 이름을 가진다.
대략적인 Component 구조는 아래와 같다.
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

