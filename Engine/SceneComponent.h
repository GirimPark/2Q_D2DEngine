#pragma once
#include <vector>
#include <cassert>
#include "Component.h"

/*--------------------------------------------------------------------
위치정보를 갖는 Component
일반적으로는 인스턴스화하지 않는다.
위치정보를 필요로 하는 컴포넌트들은 해당 컴포넌트를 상속받아 사용한다.
---------------------------------------------------------------------*/
class SceneComponent
	: public Component
{
protected:
	// m_Children : 개념적으로 가지는 자식컴포넌트 벡터. 현재는 사용되지 않는다.(2023.07.27)
	//				Object의 Component 리스트에서 모든 것을 수행한다.
	std::vector<Component*> m_Children;
	SceneComponent* m_pParentComponent = nullptr;

	framework::Vector2D m_RelativeScale = { 1.f, 1.f };
	float m_RelativeRotation = 0.f;
	framework::Vector2D m_RelativeLocation = { 0.f, 0.f };
	framework::Vector2D m_WorldLocation = { 0.f, 0.f };	// 실시간 위치값

	// RelativeScale, Rotation, Location에 대한 변환연산 결과값
	D2D_MATRIX_3X2_F m_RelativeTransform;
	D2D_MATRIX_3X2_F m_WorldTransform;
	D2D_MATRIX_3X2_F m_FinalTransform;

private:
	// 소속된 오브젝트의 부모오브젝트
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
		// 컴포넌트타입인지 확인
		assert(dynamic_cast<Component*>(childComponent));

		m_Children.push_back(childComponent);

		return childComponent;
	}
};