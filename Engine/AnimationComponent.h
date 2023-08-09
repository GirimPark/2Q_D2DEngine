#pragma once

#include "RenderComponent.h"
#include "EventListener.h"

class AnimationAsset;

/*---------------------------------------------------------------------
애니메이션 에셋 정보를 통해 실제 오브젝트에 붙을 애니메이션 컴포넌트.
FSM에서 AnimationComponent를 조작하기 위해 IAnimationNotify를 구현한다.
에셋 정보를 Save 해주고, Json 파일이 생성되면 Load 해준다.
----------------------------------------------------------------------*/
class AnimationComponent
	: public RenderComponent
	, public EventListener
{
protected:
	AnimationAsset* m_pAnimationAsset = nullptr;									// 애니메이션을 위한 기본 데이터 자산 (내부에 D2D1Bitmap)
	std::wstring m_AnimationName;													// 현재 애니메이션 이름
	size_t m_FrameIndex = 0;														// 현재 프레임 인덱스
	float m_ProgressTime = 0.f;														// 애니메이션 진행시간
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f, 0.f, 0.f };			// 시간에 따른 D2D1Bitmap의 Source 영역
	D2D1_RECT_F m_DstRect = { 0.f, 0.f, 0.f, 0.f };			// 시간에 따른 D2D1Bitmap의 Source 영역
	bool m_bMirror = false;
	float m_Speed = 1.f;

private:
	float m_Width = 0.f;
	float m_Height = 0.f;

public:
	virtual ~AnimationComponent();

public:
	void SetProgressTime(const float val) { m_ProgressTime = val; }
	void SetSpeed(const float val) { m_Speed = val; }

public:
	virtual void Update(const float deltaTime) override final;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override final;

public:
	void SetAnimationAsset(const WCHAR* szFilePath, const std::wstring animationName, std::vector<framework::FRAME_INFO>& frameInfo);
	void SetCurAnimation(const std::wstring name, const bool flip = false);
	void SetDefaultAnimationName(const std::wstring animName) { m_AnimationName = animName; }

public:
	void HandleEvent(Event* event) final;
};