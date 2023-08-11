#pragma once
#include <vector>

#include "struct.h"

class Component;
class UI;
class UIObject;
class SceneComponent;

class UIManager
{
public:
	UIManager() = default;
	~UIManager();

public:
	void Initialize(const UIObject* curUI);
	void Update(float deltaTime);
	void SetFocusedUI(UI* focusedUI);

public:
	UI* GetFocusedUI() ;
	UI* GetTargetedUI(UI* parentUI) const;

private:
	UI* m_pFocusedUI = nullptr;
	SceneComponent* m_pCurUI = nullptr;

	bool m_bMenuClicked = false;
	bool m_bColorChanged = false;

	// 1초동안 못 움직이게 하기
	bool m_bChangeFocusState = false;

	int m_childIndex = 0;

	D2D1::ColorF m_color = D2D1::ColorF::Black;

	framework::Vector2D m_finalControllerPos = { 0.f, 0.f };
	framework::Vector2D m_curControllerPos = { 0.f, 0.f };

	std::vector<std::vector<UI*>> m_UILocation;

	size_t m_curX = 0;
	size_t m_curY = 0;
};