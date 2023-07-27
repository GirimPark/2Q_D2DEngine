#pragma once

#include "resource.h"
#include "../Engine/CommonApp.h"

/*-----------------------------------
���� �����Ǵ� ���� ���ø����̼�
�Ŵ������� Init, Update, Render�Ѵ�.
-------------------------------------*/
class GameApp
	: public CommonApp
{
	World* m_pTestWorld = nullptr;

public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	void Update() override;
	void Render() override;
	bool Initialize() override;
	void Finalize() override;
};
