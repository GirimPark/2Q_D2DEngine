#pragma once
#include <list>
#include <cassert>
#include "GameObject.h"
#include "AABB.h"

/*-----------------------------------------------
World�� ���� Ŭ����
GameApp�� World ���� ������ ���带 �˻�, ��ȯ�Ѵ�.
World�� GameObject ����Ʈ�� ��� �ִ�.
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
		// todo : Ÿ�� ����ó��
		T* obj = new T;

		GameObject* castedObj = dynamic_cast<GameObject*>(obj);
		assert(castedObj);
		castedObj->SetName(objectName);

		m_GameObjects.push_back(castedObj);

		return obj;
	}
};

