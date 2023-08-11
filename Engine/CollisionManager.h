//#pragma once
//
//#include "map"
//
//class BoxCollider;
//class Object;
//
//// 충돌한 정보 저장 : left_ID + right_ID
//union COLLIDER_ID
//{
//	struct
//	{
//		UINT left_ID;
//		UINT right_ID;
//	};
//	ULONGLONG ID;
//};
//
//// class SceneManager;
//// class KeyManager;
//// class EventManager;
//
//class CollisionManager
//{
//public:
//	CollisionManager();
//
//public:
//	static CollisionManager* GetInstance()
//	{
//		if (m_pInputInstance == nullptr)
//			m_pInputInstance = new CollisionManager;
//
//		return m_pInputInstance;
//	}
//
//	void Initialize();
//	void Update(float deltaTime);
//	void Finalize();
//
//public:
//	void CheckObjectType(OBJECT_TYPE _left, OBJECT_TYPE _right);
//	static void PushBox(BoxCollider* _left, BoxCollider* _right);
//
//private:
//	void CollisionGroupUpdate(OBJECT_TYPE _left, OBJECT_TYPE _right, GameProcess* gameProcess);
//	bool IsCollision(BoxCollider* _left, BoxCollider* _right);
//
//private:
//	std::map<ULONGLONG, bool> m_mapCollisionInfo;
//	UINT m_arrCheck[(UINT)OBJECT_TYPE::END];
//
//private:
//	static CollisionManager* m_pInputInstance;
//};