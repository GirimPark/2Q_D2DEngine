#pragma once
#include <vector>

class Component;
class UI;
class UIObject;
class SceneComponent;

class UIManager
{
public:
	UIManager();

public:
	void Initialize(UIObject* curUI);
	void Update();
	void SetFocusedUI(UI* focusedUI);

public:
	UI* GetFocusedUI() ;
	UI* GetTargetedUI(UI* parentUI) const;

private:
	UI* m_pFocusedUI = nullptr;
	SceneComponent* m_pCurUI = nullptr;

	bool m_bMenuClicked = false;
	bool m_bColorChanged = false;

	D2D1::ColorF m_color = D2D1::ColorF::Black;
};