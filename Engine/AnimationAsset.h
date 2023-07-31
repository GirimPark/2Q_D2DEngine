#pragma once

#include <unordered_map>
#include <vector>
#include "ReferenceCounter.h"

/*---------------------------------------------------------------------------
애니메이션에 필요한 데이터
공통적인 애니메이션 정보의 경우 인스턴스 생성 없이 레퍼런스 카운터만으로 관리한다.
----------------------------------------------------------------------------*/
class AnimationAsset :
    public ReferenceCounter
{
// 파괴는 Release로 , 생성은 D2DRenderer가 하게한다.
public:
	AnimationAsset();
	virtual ~AnimationAsset();

public:
	ID2D1Bitmap* m_pBitmap;
	std::wstring m_BitmapFilePath;

	std::unordered_map<std::wstring, std::vector<framework::FRAME_INFO>> m_Animations;	// 애니메이션 이름, 프레임정보 맵

	void Build();

	void SetBitmapFilePath(const WCHAR* szFilePath);
};

