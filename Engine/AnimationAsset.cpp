#include "pch.h"
#include "CommonApp.h"
#include "AnimationAsset.h"

AnimationAsset::AnimationAsset()
	: m_pBitmap(nullptr)
{

}

AnimationAsset::~AnimationAsset()
{
	// 팩토리를 통해서 해제한다.
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