#pragma once

#include "GameViewObject.h"

class HLightAndNormalViewItem : public HIGameViewItem {
private:
	IDirect3DDevice9 *m_device;
	IDirect3DVertexBuffer9 *m_vertexBuff;
	IDirect3DIndexBuffer9 *m_indexBuff;
	D3DXMATRIX m_worldPos;

public:
	virtual VOID Load();
	virtual VOID Unload();
	virtual VOID Show();
	virtual VOID Hide();
	virtual VOID Update();
};