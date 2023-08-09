#pragma once

class FSMTransition
{
public:
	virtual std::pair<std::wstring, bool> operator()() abstract;
};