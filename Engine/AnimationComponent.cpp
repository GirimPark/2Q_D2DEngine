#include "pch.h"
#include "CommonApp.h"
#include "AnimationAsset.h"
#include "AnimationComponent.h"

bool AnimationComponent::Initialize()
{
	SceneComponent::Initialize();

	return true;
}

void AnimationComponent::Update()
{
	m_ProgressTime += CommonApp::m_deltaTime;
	std::vector<framework::FRAME_INFO> curAnimation = m_pAnimationAsset->m_Animations.find(m_AnimationName)->second;
	float renderTime = curAnimation[m_FrameIndex].RenderTime;
	
	// 마지막 프레임이라면 오브젝트에 애니메이션이 종료됨을 알린다.
	if (m_FrameIndex == curAnimation.size() - 1 && m_ProgressTime > renderTime)
	{
		//m_pOwner->OnAnimationEnd();
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

	__super::Update();

	CalAABB();
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

void AnimationComponent::SetAnimationAsset(const WCHAR* szFilePath, std::wstring animationName, std::vector<framework::FRAME_INFO> frameInfo)
{
	if (!m_pAnimationAsset)
		m_pAnimationAsset = new AnimationAsset;
	m_pAnimationAsset->SetBitmapFilePath(szFilePath);
	m_pAnimationAsset->Build();
	m_pAnimationAsset->m_Animations.insert(std::pair<std::wstring, std::vector<framework::FRAME_INFO>>(animationName, frameInfo));
}

void AnimationComponent::SetCurAnimation(std::wstring name, bool flip)
{
	assert(m_pAnimationAsset != nullptr);
	assert(m_pAnimationAsset->m_Animations.find(name) != m_pAnimationAsset->m_Animations.end());

	m_AnimationName = name;
	m_FrameIndex = 0;
	m_ProgressTime = 0.f;
	m_bMirror = flip;
}

void AnimationComponent::CalAABB()
{
	m_ComponentAABB.m_Center = m_WorldLocation;

	m_Width = m_SrcRect.right - m_SrcRect.left;
	m_Height = m_SrcRect.bottom - m_SrcRect.top;
	(m_Width >= m_Height) ? (m_ComponentAABB.m_Extend = m_Width / 2.f) : (m_ComponentAABB.m_Extend = m_Height / 2.f);

	m_ComponentAABB.CalCullingBox();
}