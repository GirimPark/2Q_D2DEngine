#include "pch.h"
#include "CommonApp.h"
#include "AnimationAsset.h"

AnimationAsset::AnimationAsset()
	: m_pBitmap(nullptr)
{

}

AnimationAsset::~AnimationAsset()
{
	// ���丮�� ���ؼ� �����Ѵ�.
	CommonApp::m_pInstance->GetRenderer()->ReleaseD2DBitmapFromFile(m_pBitmap);
}

void AnimationAsset::Build()
{
	CommonApp::m_pInstance->GetRenderer()->CreateD2DBitmapFromFile(m_BitmapFilePath.c_str(), &m_pBitmap);
}

void AnimationAsset::SetBitmapFilePath(const WCHAR* szFilePath)
{
	m_BitmapFilePath = szFilePath;
}