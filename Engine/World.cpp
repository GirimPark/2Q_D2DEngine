#include "pch.h"
#include "World.h"
#include "nlohmann/json.hpp"

#include "BoxCollider2D.h"
#include "CircleCollider2D.h"

World::~World()
{
	for (const auto& obj : m_GameObjects)
	{
		delete obj;
	}
	m_GameObjects.clear();
}

bool World::Initialize()
{
	for (const auto& obj : m_GameObjects)
	{
		bool res = obj->Initialize();
		assert(res);
	}

	return true;
}

void World::Update(const float deltaTime)
{
	bool trigger = false;
	for (const auto& obj : m_GameObjects)
	{
		const auto Collider = dynamic_cast<Collider2D*>(obj->GetComponent(L"Collider2D"));

		if (Collider)
			trigger = true;
	}

	if (trigger)
	{
		for (const auto& thisObj : m_GameObjects)
		{
			// Object to Object
			for (const auto& otherObj : m_GameObjects)
			{
				// ���� ������Ʈ������ �˻��� �ʿ䰡 ����
				if (thisObj == otherObj)
					continue;

				const auto thisCollider = dynamic_cast<Collider2D*>(thisObj->GetComponent(L"Collider2D"));
				const auto otherCollider = dynamic_cast<Collider2D*>(otherObj->GetComponent(L"Collider2D"));

				// �浹 �ڽ��� ��ġ���� Ȯ��
				if (thisCollider->CheckIntersect(otherCollider))
				{
					// �浹 �ڽ��� ��ģ�ٸ� �� ������Ʈ�� ���̻� �ٸ� ������Ʈ�� �˻��� �ʿ䰡 ����
					thisCollider->m_isCollision = true;

					// thisCollider�� Block() ���ش�
					thisCollider->ProcessBlock(deltaTime);
					break;
				}

				thisCollider->m_isCollision = false;
			}
		}
	}

	// Object Update
	for (const auto& obj : m_GameObjects)
	{
		obj->Update(deltaTime);
	}
}

void World::Render()
{
	// Only Won�� ��� ī�޶� �����̱� ������ ������ ����ȭ�� �ʿ� ����
	// AABB �ִ� ������ 230809 ���� Ŀ�� �� �������� ����
	for (const auto& obj : m_GameObjects)
	{
		obj->Render();
	}
}

void World::Save(const wchar_t* FilePath)
{
	nlohmann::ordered_json obj;
}