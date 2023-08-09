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