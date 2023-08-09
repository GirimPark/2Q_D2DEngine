#pragma once

#include "GameObject.h"

#include <list>
#include <cassert>

class UIObject;

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

protected:
	UIObject* m_pUIObject = nullptr;

public:
	virtual ~World();

public:
	virtual bool Initialize();
	virtual void Update(const float deltaTime);
	virtual void Render();

	void Save(const wchar_t* FilePath);

	UIObject* GetUIObject() { return m_pUIObject; }
	void SetUIObject(UIObject* UIObject) { m_pUIObject = UIObject; }

public:
	template <typename T>
	T* CreateGameObject(std::wstring objectName)
	{
		T* obj = new T;

		GameObject* castedObj = dynamic_cast<GameObject*>(obj);
		assert(castedObj);
		castedObj->SetName(objectName);

		m_GameObjects.push_back(castedObj);

		return obj;
	}
};

