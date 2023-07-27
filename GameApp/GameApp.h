#pragma once

#include "resource.h"
#include "../Engine/CommonApp.h"

/*-----------------------------------
실제 구동되는 게임 애플리케이션
매니저들을 Init, Update, Render한다.
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
