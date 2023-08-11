#pragma once

#include "../Engine/CommonApp.h"

class World;

/// <summary>
///	���� �����Ǵ� ���� ���ø����̼�
/// �Ŵ������� Init, Update, Render�Ѵ�.
/// </summary>
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
