#include "PrismaticViewItem.h"

#include "program.h"
#include "Common/CommonCode.h"

extern HProgram *g_program;

//--------·Ö½çÏß-----------------------------------------------------------------
VOID HPrismaticViewItem::Load() {
	m_device = g_program->Get_m_device();
	D3DXMatrixTranslation(&m_worldPos, 0.0f, 0.0f, 0.0f);
}

VOID HPrismaticViewItem::Unload() {

}

VOID HPrismaticViewItem::Show() {
	m_device->CreateVertexBuffer(
		6 * sizeof(HXYZCVertex),
		D3DUSAGE_WRITEONLY,
		HXYZCVertex::FVF,
		D3DPOOL_MANAGED,
		&m_vertexBuff,
		0
	);
	HXYZCVertex *vertexBuf;
	m_vertexBuff->Lock(0, 0, (VOID**)(&vertexBuf), 0);
	{
		int i = 0;
		vertexBuf[i++] = HXYZCVertex(1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 127, 127));
		vertexBuf[i++] = HXYZCVertex(-1.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(0, 127, 127));

		vertexBuf[i++] = HXYZCVertex(0.0f, 1.0f, 0.0f, D3DCOLOR_XRGB(127, 255, 127));
		vertexBuf[i++] = HXYZCVertex(0.0f, -1.0f, 0.0f, D3DCOLOR_XRGB(127, 0, 127));

		vertexBuf[i++] = HXYZCVertex(0.0f, 0.0f, 1.0f, D3DCOLOR_XRGB(127, 127, 255));
		vertexBuf[i++] = HXYZCVertex(0.0f, 0.0f, -1.0f, D3DCOLOR_XRGB(127, 127, 0));
	}
	m_vertexBuff->Unlock();

	m_device->CreateIndexBuffer(
		24 * sizeof(DWORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&m_indexBuff,
		0
	);
	DWORD *indexBuf;
	m_indexBuff->Lock(0, 0, (VOID**)(&indexBuf), 0);
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
	m_indexBuff->Unlock();
}

VOID HPrismaticViewItem::Hide() {

}

VOID HPrismaticViewItem::Update() {
	m_device->SetTransform(D3DTS_WORLD, &m_worldPos);
	m_device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);

	m_device->BeginScene();
	{
		m_device->SetStreamSource(0, m_vertexBuff, 0, sizeof(HXYZCVertex));
		m_device->SetFVF(HXYZCVertex::FVF);
		m_device->SetIndices(m_indexBuff);
		m_device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 8);
	}
	m_device->EndScene();
}

