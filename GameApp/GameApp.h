#pragma once

#include "../Engine/CommonApp.h"

class World;

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
	~GameApp() override;

	void Update() override;
	void Render() override;
	bool Initialize() override;
	void Finalize() override;
};
