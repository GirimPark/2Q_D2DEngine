#include "pch.h"
#include "GameObject.h"
#include "SceneComponent.h"

bool SceneComponent::Initialize()
{
	// 렌더컴포넌트를 상속받은 경우 각 컴포넌트의 컬링박스를 지정해주는 Init이 존재한다
	// 현재 사용 x
	m_pParentObject = m_pOwner->GetOwnerObj();
	//this->GetName() == L"CameraComponent"
	UpdateTransform();

	return true;
}

void SceneComponent::Update()
{
	UpdateTransform();
}

void SceneComponent::UpdateTransform()
{
	// 복합 변환 - SRT
	if (m_RelativeRotation >= 360.f)	m_RelativeRotation -= 360.f;

	m_RelativeTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(m_RelativeScale.x, m_RelativeScale.y))
		* D2D1::Matrix3x2F::Rotation(m_RelativeRotation)
		* D2D1::Matrix3x2F::Translation(m_RelativeLocation.x, m_RelativeLocation.y);

	// worldTransform 계산
	if (m_pParentComponent)
	{
		m_WorldTransform = m_RelativeTransform * m_pParentComponent->m_WorldTransform;
		m_WorldLocation = { m_WorldTransform.dx, m_WorldTransform.dy };
	}
	else // root component인 경우
	{
		if (m_pParentObject)
		{
			m_WorldTransform = m_RelativeTransform * m_pParentObject->GetRootComponent()->m_WorldTransform;
		}
		else
		{
			m_WorldTransform = m_RelativeTransform;
		}
		m_WorldLocation = { m_WorldTransform.dx, m_WorldTransform.dy };

	}
}

void SceneComponent::AttachToComponent(SceneComponent* pParent)
{
	m_pParentComponent = pParent;
	pParent->m_Children.push_back(this);
}