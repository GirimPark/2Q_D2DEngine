#pragma once

/// <summary>
///	�ν��Ͻ�ȭ�� FSMTransition�� ����
///	��ȯ ������ �ش� Functor�� �����Ѵ�.
///	</summary>
class FSMTransition
{
public:
	virtual std::pair<std::wstring, bool> operator()() abstract;
};