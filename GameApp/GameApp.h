#pragma once

#include "../Engine/CommonApp.h"
//#include "../D2DRenderer/D2DRenderer.h"

class GameApp
	: public CommonApp
{
public:
	GameApp(HINSTANCE hInstance);
	~GameApp();

	virtual void Update() override;
	void Render() override;
	virtual bool Initialize() override;
};

