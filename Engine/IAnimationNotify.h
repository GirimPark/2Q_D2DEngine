#pragma once

/*-----------------------------------------------------------------------
애니메이션 정보를 FSMComponent로 전달하기 위한 인터페이스
GameObject가 해당 인터페이스를 상속받아 각자의 OnAnimationEnd()를 구현한다.
------------------------------------------------------------------------*/
class IAnimationNotify
{
	virtual void OnAnimationEnd() abstract;
};