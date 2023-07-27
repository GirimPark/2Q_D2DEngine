#include "pch.h"
#include "GameObject.h"
#include "World.h"

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
	return false;
}

void World::Update()
{
}

void World::Render()
{
}

void World::RenderInformation()
{
}
