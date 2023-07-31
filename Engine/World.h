#pragma once
#include <list>
#include <cassert>
#include "GameObject.h"
#include "AABB.h"

/*-----------------------------------------------
World의 원형 클래스
GameApp은 World 맵을 가지고 월드를 검색, 전환한다.
World는 GameObject 리스트를 들고 있다.
------------------------------------------------*/
class World
{
private:
	std::list<GameObject*> m_GameObjects;
	std::list<GameObject*> m_RenderGameObjects;
	AABB m_CameraAABB;

public:
	virtual ~World();

public:
	virtual bool Initialize();
	virtual void Update();
	virtual void Render();

private:
	void RenderInformation();

public:
	template <typename T>
	T* CreateGameObject(std::wstring objectName)
	{
		// todo : 타입 예외처리
		T* obj = new T;

		GameObject* castedObj = dynamic_cast<GameObject*>(obj);
		assert(castedObj);
		castedObj->SetName(objectName);

		m_GameObjects.push_back(castedObj);

		return obj;
	}
};

