#pragma once
#include "RenderComponent.h"

class TextureAsset;
class TextureComponent
	: public RenderComponent
{
private:
	TextureAsset* m_pTextureAsset = nullptr;
	bool m_bMirrorX = false;
	bool m_bMirrorY = false;
	D2D1::ColorF m_Color = D2D1::ColorF::Black;

public:
	TextureComponent();
	~TextureComponent() override;

public:
	void SetTextureAsset(const WCHAR* szFilePath, const std::wstring textureName);
	void SetFlipX(bool flipX) { m_bMirrorX = flipX; }
	void SetFlipY(bool flipY) { m_bMirrorY = flipY; }
	void SetColor(D2D1::ColorF color) { m_Color = color; }

public:
	void Render(ID2D1RenderTarget* pRenderTarget) final;
};

