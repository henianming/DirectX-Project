#pragma once

#include "GameViewObject.h"
#include <d3d9.h>

class HTextureViewItem : public HIGameViewItem {
private:
	IDirect3DDevice9 *m_device;
	D3DXMATRIX m_worldPos;
	IDirect3DVertexBuffer9 *m_vertexBuf;
	IDirect3DTexture9 *m_texture_top;
	IDirect3DTexture9 *m_texture_bottom;
	IDirect3DTexture9 *m_texture_front;
	IDirect3DTexture9 *m_texture_side;

private:
	VOID Sence();

public:
	virtual VOID Load();
	virtual VOID Unload();
	virtual VOID Show();
	virtual VOID Hide();
	virtual VOID Update();
};