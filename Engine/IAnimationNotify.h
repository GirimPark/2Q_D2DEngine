#pragma once

/*-----------------------------------------------------------------------
�ִϸ��̼� ������ FSMComponent�� �����ϱ� ���� �������̽�
GameObject�� �ش� �������̽��� ��ӹ޾� ������ OnAnimationEnd()�� �����Ѵ�.
------------------------------------------------------------------------*/
class IAnimationNotify
{
	virtual void OnAnimationEnd() abstract;
};