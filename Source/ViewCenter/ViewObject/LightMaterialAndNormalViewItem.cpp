#include "LightMaterialAndNormalViewItem.h"

#include "program.h"
#include "Common/CommonCode.h"

extern HProgram *g_program;

VOID HLightMaterialAndNormalViewItem::Load() {
	m_device = g_program->Get_m_device();
	R_NULL(m_device);

	D3DXMatrixTranslation(&m_worldPos, 2.0f, 2.0f, 2.0f);

	m_material.Diffuse = D3DXCOLOR(D3DCOLOR_XRGB(255, 255, 255));
	m_material.Ambient = D3DXCOLOR(D3DCOLOR_XRGB(255, 255, 255));
	m_material.Specular = D3DXCOLOR(D3DCOLOR_XRGB(255, 255, 255));
	m_material.Emissive = D3DXCOLOR(D3DCOLOR_XRGB(0, 0, 0));
	m_material.Power = 5.0f;

	::ZeroMemory(&m_light, sizeof(m_light));
	m_light.Type = D3DLIGHT_DIRECTIONAL;
	m_light.Diffuse = D3DXCOLOR(D3DCOLOR_XRGB(255, 255, 255));
	m_light.Specular = D3DXCOLOR(D3DCOLOR_XRGB(255, 255, 255)) * 0.3f;
	m_light.Ambient = D3DXCOLOR(D3DCOLOR_XRGB(255, 255, 255)) * 0.6f;
	m_light.Direction = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
}

VOID HLightMaterialAndNormalViewItem::Unload() {

}

VOID HLightMaterialAndNormalViewItem::Show() {
	R_HR_FAILED(
		m_device->CreateVertexBuffer(
			8 * sizeof(HXYZNVertex),
			D3DUSAGE_WRITEONLY,
			HXYZNVertex::FVF,
			D3DPOOL_MANAGED,
			&m_vertexBuff,
			0
		)
	);
	HXYZNVertex *vertexBuf;
	R_HR_FAILED(m_vertexBuff->Lock(0, 0, (VOID**)(&vertexBuf), 0));
	{
		int i = 0;
		vertexBuf[i++] = HXYZNVertex(1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
		vertexBuf[i++] = HXYZNVertex(-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f);

		vertexBuf[i++] = HXYZNVertex(0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f);
		vertexBuf[i++] = HXYZNVertex(0.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f);

		vertexBuf[i++] = HXYZNVertex(0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);
		vertexBuf[i++] = HXYZNVertex(0.0f, 0.0f, -1.0f, 0.0f, 0.0f, -1.0f);
	}
	R_HR_FAILED(m_vertexBuff->Unlock());

	R_HR_FAILED(
		m_device->CreateIndexBuffer(
			24 * sizeof(DWORD),
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX32,
			D3DPOOL_MANAGED,
			&m_indexBuff,
			0
		)
	);
	DWORD *indexBuf;
	R_HR_FAILED(m_indexBuff->Lock(0, 0, (VOID**)(&indexBuf), 0));
	{
		DWORD tempBuf[24] = {
			2, 0, 5,
			2, 5, 1,
			2, 1, 4,
			2, 4, 0,
			3, 5, 0,
			3, 0, 4,
			3, 4, 1,
			3, 1, 5
		};
		for (int i = 0; i < 24; i++) {
			indexBuf[i] = tempBuf[i];
		}
	}
	R_HR_FAILED(m_indexBuff->Unlock());
}

VOID HLightMaterialAndNormalViewItem::Hide() {
	if (m_indexBuff != NULL) {
		m_indexBuff->Release();
		m_indexBuff = NULL;
	}

	if (m_vertexBuff != NULL) {
		m_vertexBuff->Release();
		m_vertexBuff = NULL;
	}
}

VOID HLightMaterialAndNormalViewItem::Update() {
	m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_device->SetRenderState(D3DRS_LIGHTING, TRUE);
	m_device->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
	m_device->SetRenderState(D3DRS_SPECULARENABLE, TRUE);

	m_device->SetTransform(D3DTS_WORLD, &m_worldPos);

	m_device->SetMaterial(&m_material);

	m_device->SetLight(0, &m_light);
	m_device->LightEnable(0, TRUE);

	m_device->BeginScene();
	{
		m_device->SetStreamSource(0, m_vertexBuff, 0, sizeof(HXYZNVertex));
		m_device->SetFVF(HXYZNVertex::FVF);
		m_device->SetIndices(m_indexBuff);
		m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 8);
	}
	m_device->EndScene();
}
