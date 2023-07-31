#pragma once
#include <vector>
#include <cassert>
#include "Component.h"

/*--------------------------------------------------------------------
��ġ������ ���� Component
�Ϲ������δ� �ν��Ͻ�ȭ���� �ʴ´�.
��ġ������ �ʿ�� �ϴ� ������Ʈ���� �ش� ������Ʈ�� ��ӹ޾� ����Ѵ�.
---------------------------------------------------------------------*/
class SceneComponent
	: public Component
{
protected:
	// m_Children : ���������� ������ �ڽ�������Ʈ ����. ����� ������ �ʴ´�.(2023.07.27)
	//				Object�� Component ����Ʈ���� ��� ���� �����Ѵ�.
	std::vector<Component*> m_Children;
	SceneComponent* m_pParentComponent = nullptr;

	framework::Vector2D m_RelativeScale = { 1.f, 1.f };
	float m_RelativeRotation = 0.f;
	framework::Vector2D m_RelativeLocation = { 0.f, 0.f };
	framework::Vector2D m_WorldLocation = { 0.f, 0.f };	// �ǽð� ��ġ��

	// RelativeScale, Rotation, Location�� ���� ��ȯ���� �����
	D2D_MATRIX_3X2_F m_RelativeTransform;
	D2D_MATRIX_3X2_F m_WorldTransform;
	D2D_MATRIX_3X2_F m_FinalTransform;

private:
	// �Ҽӵ� ������Ʈ�� �θ������Ʈ
	GameObject* m_pParentObject = nullptr;


public:
	virtual ~SceneComponent() { }

public:
	//void SetRelativeScale(float x, float y) { m_RelativeScale.x = x; m_RelativeScale.y = y; }
	//Vector2D GetRelativeScale() { return m_RelativeScale; }
	//void SetRelativeRotation(float rotation) { m_RelativeRotation = rotation; }
	//float GetRelativeRotation() { return m_RelativeRotation; }
	void SetRelativeLocation(float x, float y) { m_RelativeLocation.x = x; m_RelativeLocation.y = y; }
	framework::Vector2D GetRelativeLocation() { return m_RelativeLocation; }
	framework::Vector2D GetWorldLocation() { return m_WorldLocation; }
	framework::Vector2D GetFinalLocation() { return { m_FinalTransform.dx, m_FinalTransform.dy }; }
	//D2D_MATRIX_3X2_F GetWorldTransform() { return m_WorldTransform; }
	//D2D_MATRIX_3X2_F GetFinalTransform() { return m_FinalTransform; }

	void AddRelativeRotation(float rotation) { m_RelativeRotation = m_RelativeRotation + rotation; UpdateTransform(); }
	void AddRelativeLocation(float x, float y) { m_RelativeLocation.x += x; m_RelativeLocation.y += y; }

	virtual bool Initialize();
	virtual void Update() override;

protected:
	void UpdateTransform();

public:
	void AttachToComponent(SceneComponent* pParent);

public:
	template <typename T>
	T* CreateChild()
	{
		T* childComponent = new T;
		// ������ƮŸ������ Ȯ��
		assert(dynamic_cast<Component*>(childComponent));

		m_Children.push_back(childComponent);

		return childComponent;
	}
};