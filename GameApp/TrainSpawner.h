#pragma once

#include "../Engine/GameObject.h"

#include <vector>

enum class TRAIN_DROP_TYPE;

class TrainSpawner :
    public GameObject
{
private:
    float m_ElaspedDelayTime = 0.f;
    float m_DelayTime = 4.f;
    float m_ElapsedSpawnTime = 0.f;
    float m_SpawnTime = 5.f;
    std::vector<framework::Vector2D> m_SpawnPositions;
    static TRAIN_DROP_TYPE m_DropTypeArr[3];

public:
    TrainSpawner();
    ~TrainSpawner() final;

public:
    bool Initialize() final;
    void Update(float deltaTime) final;

public:
    float GetSpawnTime() const { return m_SpawnTime; }
    void SetSpawnTime(const float spawnTime) { m_SpawnTime = spawnTime; }

    void AddSpawnPosition(const framework::Vector2D& spawnPosition) { m_SpawnPositions.push_back(spawnPosition); }
};