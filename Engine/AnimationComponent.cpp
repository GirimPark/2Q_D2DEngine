#include "pch.h"
#include "AnimationComponent.h"

#include "CommonApp.h"
#include "AnimationAsset.h"
#include "GameObject.h"
#include "EventManager.h"

AnimationComponent::~AnimationComponent()
{
	if (m_pAnimationAsset)
	{
		delete m_pAnimationAsset;
	}
}

void AnimationComponent::Update(const float deltaTime)
{
	m_ProgressTime += deltaTime;
	std::vector<framework::FRAME_INFO> curAnimation = m_pAnimationAsset->m_Animations.find(m_AnimationName)->second;
	float renderTime = curAnimation[m_FrameIndex].RenderTime;

	// ������ �������̶�� ������Ʈ�� �ִϸ��̼��� ������� �˸���.
	if (m_FrameIndex == curAnimation.size() - 1 && m_ProgressTime > renderTime)
	{
		EventManager::GetInstance()->SendEvent(eEventType::AnimationEnd);
		m_ProgressTime = 0.f;
	}

	if (m_ProgressTime > renderTime)
	{
		m_ProgressTime -= renderTime;
		m_FrameIndex = (m_FrameIndex + 1) % (curAnimation.size());
		m_SrcRect = curAnimation[m_FrameIndex].Source;
		m_DstRect = { -(m_SrcRect.right - m_SrcRect.left) / 2.f, -(m_SrcRect.bottom - m_SrcRect.top) / 2.f,
			(m_SrcRect.right - m_SrcRect.left) / 2.f, (m_SrcRect.bottom - m_SrcRect.top) / 2.f };
	}

	__super::Update(deltaTime);
}

void AnimationComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if (m_bMirror)
	{
		m_WorldTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(-1.f, 1.f))
			* m_WorldTransform;
	}
	m_FinalTransform = m_WorldTransform * GetCameraTransform();
	pRenderTarget->SetTransform(m_FinalTransform);

	pRenderTarget->DrawBitmap(
		m_pAnimationAsset->m_pBitmap,
		m_DstRect,
		1.f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		m_SrcRect);

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void AnimationComponent::SetAnimationAsset(const WCHAR* szFilePath, const std::wstring animationName, std::vector<framework::FRAME_INFO>& frameInfo)
{
	if (!m_pAnimationAsset)
		m_pAnimationAsset = new AnimationAsset;
	m_pAnimationAsset->SetBitmapFilePath(szFilePath);
	m_pAnimationAsset->Build();
	// todo(ä��) : �̹� ����Ǿ� �־ save�� �ּ�ó�� �س���
	// ���߿� ���� �� ������ �ٽ� Save �������. �׸��� Asset �̸� �ٲ���
	m_pAnimationAsset->m_Animations.insert(std::pair<std::wstring, std::vector<framework::FRAME_INFO>>(animationName, frameInfo));
	m_pAnimationAsset->Save(L"../Resource/TestWorld.WorldAsset");
	//m_pAnimationAsset->Load(L"../Resource/TestWorld.WorldAsset");
}

void AnimationComponent::SetCurAnimation(const std::wstring name, const bool flip)
{
	assert(m_pAnimationAsset != nullptr);
	assert(m_pAnimationAsset->m_Animations.find(name) != m_pAnimationAsset->m_Animations.end());

	m_AnimationName = name;
	m_FrameIndex = 0;
	m_ProgressTime = 0.f;
	m_bMirror = flip;
}

void AnimationComponent::HandleEvent(Event* event)
{
	if(event->eventID == eEventType::ChangeCurAnimation)
	{
		SetCurAnimation(event->animationInfo.animationName, event->animationInfo.flip);
	}
	else if(event->eventID == eEventType::SetDefaultAnimation)
	{
		m_AnimationName = event->animationInfo.animationName;
	}
}
