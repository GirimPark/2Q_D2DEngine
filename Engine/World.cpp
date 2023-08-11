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
				// 같은 오브젝트끼리는 검사할 필요가 없다
				if (thisObj == otherObj)
					continue;

				const auto thisCollider = dynamic_cast<Collider2D*>(thisObj->GetComponent(L"Collider2D"));
				const auto otherCollider = dynamic_cast<Collider2D*>(otherObj->GetComponent(L"Collider2D"));

				// 충돌 박스가 겹치는지 확인
				if (thisCollider->CheckIntersect(otherCollider))
				{
					// 충돌 박스가 겹친다면 이 오브젝트는 더이상 다른 오브젝트와 검사할 필요가 없다
					thisCollider->m_isCollision = true;

					// thisCollider를 Block() 해준다
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
	// Only Won의 경우 카메라가 고정이기 때문에 렌더링 최적화가 필요 없음
	// AABB 있는 버전은 230809 오후 커밋 전 리비전에 있음
	for (const auto& obj : m_GameObjects)
	{
		obj->Render();
	}
}

void World::Save(const wchar_t* FilePath)
{
	nlohmann::ordered_json obj;
}