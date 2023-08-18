#include "pch.h"
#include "CollisionManager.h"

#include "World.h"

#include "BoxCollider2D.h"

void CollisionManager::Initialize()
{
	// ��� �׷��� ������ ��ȸ
	for (UINT i = 0; i < static_cast<UINT>(GROUP_TYPE::END); ++i)
	{
		for (UINT j = i; j < static_cast<UINT>(GROUP_TYPE::END); ++j)
			m_CollCheckArr[i][j] = m_CollCheckArr[j][i] = false;
	}
}

void CollisionManager::Update(float deltaTime, const std::vector<GameObject*>* gameObjects)
{
	// Player, Item, Environment, UI, ..
	for (UINT i = 0; i < static_cast<UINT>(GROUP_TYPE::END); ++i)
	{
		// Player, Item, Environment, UI, ..
		// j = i�� A -> B�� �����ϰ� B -> A�� ���� �ʴ´�
		for (UINT j = i; j < static_cast<UINT>(GROUP_TYPE::END); ++j)
		{
			// i �׷�� j �׷��� �浹üũ�� �ʿ��� �������� Ȯ��
			if (m_CollCheckArr[i][j] == true && m_CollCheckArr[j][i] == true)
			{
				// i �׷�� j �׷��� ������Ʈ ����Ʈ�� �����´�
				const std::vector<GameObject*>& thisGroup  = gameObjects[i];
				const std::vector<GameObject*>& otherGroup = gameObjects[j];

				// �׷찣 �浹üũ
				CollisionGroupUpdate(thisGroup, otherGroup, deltaTime);
			}
		}
	}
}

void CollisionManager::Finalize()
{
}

void CollisionManager::EnableCollisionType(GROUP_TYPE left, GROUP_TYPE right)
{
	m_CollCheckArr[static_cast<UINT>(left)][static_cast<UINT>(right)] = true;
	m_CollCheckArr[static_cast<UINT>(right)][static_cast<UINT>(left)] = true;
}

void CollisionManager::CollisionGroupUpdate(const std::vector<GameObject*>& thisGroup, const std::vector<GameObject*>& otherGroup, float deltaTime)
{
	// thisGroup ��ȸ
	for (UINT i = 0; i < thisGroup.size(); ++i)
	{
		const std::vector<Collider2D*> thisColliders = thisGroup[i]->GetComponents<Collider2D>();
		for(Collider2D* thisCollider : thisColliders)
		{
			if (!thisCollider)
				continue;

			// ���� �׷��̸� �ߺ� ������ ���� j=i ���� ����
			const UINT startJ = (thisGroup == otherGroup) ? i : 0;

			// otherGroup ��ȸ
			for (UINT j = startJ; j < otherGroup.size(); ++j)
			{
				// ���� ������Ʈ������ �˻��� �ʿ䰡 ����
				if (thisGroup[i] == otherGroup[j])
					continue;

				const std::vector<Collider2D*> otherColliders = otherGroup[j]->GetComponents<Collider2D>();
				for (Collider2D* otherCollider : otherColliders)
				{
					if (!otherCollider)
						continue;

					/// �� �浹ü ���̵� ���� left + right
					COLLIDER_ID colliderID = {};

					// �� �浹ü�� ID�� �����´� -> left�� right�� ID�� �������� ID�� �����Ѵ� (���� �޸𸮰��� ���)
					colliderID.left_ID = thisCollider->GetID();
					colliderID.right_ID = otherCollider->GetID();

					// �浹ü�� ID�� ã�´�
					auto iter = m_mapCollisionInfo.find(colliderID.ID);

					// �浹 ID�� ������ ���� ����
					if (m_mapCollisionInfo.end() == iter)
					{
						// map�� �浹 ID, �浹 ���θ� ����
						m_mapCollisionInfo.insert(std::make_pair(colliderID.ID, false));
						// �浹 ID�� Iterator�� �����´�
						iter = m_mapCollisionInfo.find(colliderID.ID);
					}

					/// iter->second : �� �浹ü ������ �浹 ����

					// �� �ݶ��̴��� �浹�� ���
					if (thisCollider->CheckIntersect(otherCollider))
					{
						// �浹 Ÿ���� Collision�� ��� // But �ϳ��� NONE�̸� �浹 X
						if ((thisCollider->m_CollisionType == COLLISION_TPYE::COLLISION && otherCollider->m_CollisionType == COLLISION_TPYE::COLLISION) &&
								(thisCollider->m_CollisionType != COLLISION_TPYE::NONE && otherCollider->m_CollisionType != COLLISION_TPYE::NONE))
						{
							// �̹� �浹�� �ִ� ���
							if (iter->second)
							{
								thisCollider->TurnOn_IsCollision(otherCollider);

								iter->second = true;

								thisCollider->OnCollisionStay(otherCollider);
								otherCollider->OnCollisionStay(thisCollider);
							}
							// ó�� �浹�ϴ� ���
							else
							{
								thisCollider->TurnOn_IsCollision(otherCollider);

								thisCollider->OnCollisionEnter(otherCollider);
								otherCollider->OnCollisionEnter(thisCollider);

								iter->second = true;
							}

							// A �ݶ��̴�->ProcessBlock(B �ݶ��̴�) : A �ݶ��̴��� B �ݶ��̴��� ���� "�з�����"
							thisCollider->ProcessBlock(otherCollider);
							//otherCollider->ProcessBlock(thisCollider);
						}
						// �浹 Ÿ���� Trigger�� ��� (�� �ݶ��̴��� TRIGGER�� Ʈ���� �ߵ�)
						else if ((thisCollider->m_CollisionType == COLLISION_TPYE::TRIGGER || otherCollider->m_CollisionType == COLLISION_TPYE::TRIGGER) &&
									(thisCollider->m_CollisionType != COLLISION_TPYE::NONE && otherCollider->m_CollisionType != COLLISION_TPYE::NONE))
						{
							// �̹� �浹�� �ִ� ���
							if (iter->second)
							{
								thisCollider->TurnOn_IsTrigger(otherCollider);

								iter->second = true;

								thisCollider->OnTriggerStay(otherCollider);
								otherCollider->OnTriggerStay(thisCollider);
							}
							// ó�� �浹�ϴ� ���
							else
							{
								thisCollider->TurnOn_IsTrigger(otherCollider);

								iter->second = true;

								thisCollider->OnTriggerEnter(otherCollider);
								otherCollider->OnTriggerEnter(thisCollider);
							}
						}
					}
					// �� �ݶ��̴��� �浹���� ���� ���
					else
					{
						// �浹 Ÿ���� Collision�� ���
						if ((thisCollider->m_CollisionType == COLLISION_TPYE::COLLISION && otherCollider->m_CollisionType == COLLISION_TPYE::COLLISION) &&
								(thisCollider->m_CollisionType != COLLISION_TPYE::NONE && otherCollider->m_CollisionType != COLLISION_TPYE::NONE))
						{
							// �̹� �浹�� �־��� ���
							if (iter->second)
							{
								thisCollider->TurnOff_IsCollision(otherCollider);

								iter->second = false;

								thisCollider->OnCollisionExit(otherCollider);
								otherCollider->OnCollisionExit(thisCollider);
							}
							else
							{
								iter->second = false;
							}
						}
						// �浹 Ÿ���� Trigger�� ���
						else if ((thisCollider->m_CollisionType == COLLISION_TPYE::TRIGGER || otherCollider->m_CollisionType == COLLISION_TPYE::TRIGGER) &&
									(thisCollider->m_CollisionType != COLLISION_TPYE::NONE && otherCollider->m_CollisionType != COLLISION_TPYE::NONE))
						{
							// �̹� �浹�� �־��� ���
							if (iter->second)
							{
								thisCollider->TurnOff_IsTrigger(otherCollider);

								iter->second = false;

								thisCollider->OnTriggerExit(otherCollider);
								otherCollider->OnTriggerExit(thisCollider);
							}
							else
							{
								iter->second = false;
							}
						}
					}
				}
			}
		}
	}
}