#pragma once
#include "RenderComponent.h"


/*-------------------------------------------
�ִϸ��̼� ���� ������ ���� ���� ������Ʈ�� ���� �ִϸ��̼� ������Ʈ.

-------------------------------------------*/
class AnimationComponent
	: public RenderComponent
{
protected:
	AnimationAsset* m_pAnimationAsset = nullptr;		// �ִϸ��̼��� ���� �⺻ ������ �ڻ� (���ο� D2D1Bitmap)
	std::wstring m_AnimationName;		// ���� �ִϸ��̼� �̸�
	size_t m_FrameIndex = 0;				// ���� ������ �ε���
	float m_ProgressTime = 0.f;				// �ִϸ��̼� ����ð�
	D2D1_RECT_F m_SrcRect = { 0.f, 0.f, 0.f, 0.f };			// �ð��� ���� D2D1Bitmap�� Source ����
	D2D1_RECT_F m_DstRect = { 0.f, 0.f, 0.f, 0.f };			// �ð��� ���� D2D1Bitmap�� Source ����		
	bool m_bMirror = false;
	float m_Speed = 1.f;

private:
	float m_Width = 0.f;
	float m_Height = 0.f;

public:
	void SetProgressTime(float val) { m_ProgressTime = val; }
	void SetSpeed(float val) { m_Speed = val; }

public:
	virtual bool Initialize() override;
	virtual void Update() override;
	virtual void Render(ID2D1RenderTarget* pRenderTarget) override;

public:
	void SetAnimationAsset(const WCHAR* szFilePath, std::wstring animationName, std::vector<framework::FRAME_INFO> frameInfo);
	void SetCurAnimation(std::wstring name, bool flip = false);
	void SetDefaultAnimationName(std::wstring animName) { m_AnimationName = animName; }

private:
	void CalAABB() override;
};

