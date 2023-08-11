#pragma once

#include "RenderComponent.h"
#include "EventListener.h"

class AnimationAsset;

/// <summary>
/// �ִϸ��̼� ���� ������ ���� ���� ������Ʈ�� ���� �ִϸ��̼� ������Ʈ.
/// FSM���� AnimationComponent�� �����ϱ� ���� HandleEvent�� �����Ѵ�.
/// ���� ������ Save ���ְ�, Json ������ �����Ǹ� Load ���ش�.
/// </summary>
class AnimationComponent
	: public RenderComponent
	, public EventListener
{
protected:
	AnimationAsset* m_pAnimationAsset = nullptr;									// �ִϸ��̼��� ���� �⺻ ������ �ڻ� (���ο� D2D1Bitmap)
	std::wstring m_AnimationName;													// ���� �ִϸ��̼� �̸�
	size_t m_FrameIndex = 0;														// ���� ������ �ε���
	float m_ProgressTime;														// �ִϸ��̼� ����ð�
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f, 0.f, 0.f };			// �ð��� ���� D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect = { 0.f, 0.f, 0.f, 0.f };			// �ð��� ���� D2D1Bitmap�� Source ����
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
	void Update(const float deltaTime) final;
	void Render(ID2D1RenderTarget* pRenderTarget) final;

public:
	void SetAnimationAsset(const WCHAR* szFilePath, const std::wstring animationName, std::vector<framework::FRAME_INFO>& frameInfo);
	void ChangeAnimation(const std::wstring name, const bool flip);
	void KeepAnimation(const bool flip);

public:
	void HandleEvent(Event* event) final;
};