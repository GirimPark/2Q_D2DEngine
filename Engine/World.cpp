#include "pch.h"
#include "World.h"
#include "nlohmann/json.hpp"


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
	for (auto& obj : m_GameObjects)
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