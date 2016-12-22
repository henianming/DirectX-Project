#pragma once

#include "GameViewObject.h"
#include <d3d9types.h>

class HLightAndNormalViewItem : public HIGameViewItem {
private:
	IDirect3DDevice9 *m_device;
	IDirect3DVertexBuffer9 *m_vertexBuff;
	IDirect3DIndexBuffer9 *m_indexBuff;
	D3DXMATRIX m_worldPos;

	D3DMATERIAL9 m_material;

	D3DLIGHT9 m_light;

public:
	virtual VOID Load();
	virtual VOID Unload();
	virtual VOID Show();
	virtual VOID Hide();
	virtual VOID Update();
};