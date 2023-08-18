#include "pch.h"
#include "TextureComponent.h"

#include "CommonApp.h"
#include "TextureAsset.h"

TextureComponent::TextureComponent()
{
	m_pTextureAsset = new TextureAsset;
}

TextureComponent::~TextureComponent()
{
	delete m_pTextureAsset;
}

void TextureComponent::Render(ID2D1RenderTarget* pRenderTarget)
{
	if(m_bMirrorX)
	{
		m_WorldTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(-1.f, 1.f))
			* m_WorldTransform;
	}

	if (m_bMirrorY)
	{
		m_WorldTransform = D2D1::Matrix3x2F::Scale(D2D1::SizeF(1.f, -1.f))
			* m_WorldTransform;
	}

	m_FinalTransform = m_WorldTransform * GetCameraTransform();
	pRenderTarget->SetTransform(m_FinalTransform);

	D2D1_SIZE_F size = m_pTextureAsset->m_pBitmap->GetSize();
	pRenderTarget->DrawBitmap(
		m_pTextureAsset->m_pBitmap,
		{ -size.width / 2.f, -size.height / 2.f, size.width / 2.f, size.height / 2.f },
		1.f,
		D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
		{ 0.f, 0.f, size.width, size.height });

	SetColor(D2D1::ColorF::Red);
	CommonApp::m_pInstance->GetBrush()->SetColor(m_Color);

	// Draw Text Object Name
	pRenderTarget->DrawTextW(
		m_pOwner->GetName().c_str(),
		static_cast<UINT32>(m_pOwner->GetName().length()),
		CommonApp::m_pInstance->GetTextFormat(),
		D2D1::RectF(-50, -150, 50, -50),
		CommonApp::m_pInstance->GetBrush()
	);

	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}

void TextureComponent::SetTextureAsset(const WCHAR* szFilePath, const std::wstring textureName)
{
	m_pTextureAsset->SetBitmapFilePath(szFilePath);
	m_pTextureAsset->Build();
}
