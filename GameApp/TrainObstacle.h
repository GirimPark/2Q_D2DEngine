#pragma once

#include "../Engine/GameObject.h"

enum class TRAIN_DROP_TYPE
{
    NONE,
    MONEY,
    ITEM,

    END
};

class TextureComponent;
class BoxComponent;
class BoxCollider2D;

class TrainObstacle :
    public GameObject
{
private:
    TextureComponent* m_pTextureComponent = nullptr;
    BoxComponent* m_pBoxComponent = nullptr;
    BoxCollider2D* m_pBoxCollider2D = nullptr;
    BoxCollider2D* m_pHeadBoxCollider = nullptr;

private:
    TRAIN_DROP_TYPE m_DropType = TRAIN_DROP_TYPE::NONE;
    float m_Speed = 500.f;
    int m_Direction = 1;
    framework::Vector2D m_SpawnPosition = { 0.f, 0.f };

public:
    TrainObstacle();
    ~TrainObstacle() final;

public:
    bool Initialize() final;
    void Update(float deltaTime) final;

public:
	float GetSpeed() const { return m_Speed; }
	void SetSpeed(const float speed) { m_Speed = speed; }

    int GetDirection() const { return m_Direction; }
    void SetDirection(const int direction) { m_Direction = direction; }

    TRAIN_DROP_TYPE GetDropType() const { return m_DropType; }
    void SetDropType(const TRAIN_DROP_TYPE dropType) { m_DropType = dropType; }

    framework::Vector2D GetSpawnPosition() const { return m_SpawnPosition; }
    void SetSpawnPosition(const framework::Vector2D& spawnPosition) { m_SpawnPosition = spawnPosition; }
    void SetSpawnPosition(float x, float y) { m_SpawnPosition = { x,y }; }
};