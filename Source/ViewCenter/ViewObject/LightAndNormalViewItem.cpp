#include "LightAndNormalViewItem.h"

#include "program.h"
#include "Common/CommonCode.h"

extern HProgram *g_program;

VOID HLightAndNormalViewItem::Load() {
	m_device = g_program->Get_m_device();
	R_NULL(m_device);

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
	R_HR_FAILED(m_indexBuff->Lock(0, 0, (VOID**)(indexBuf), 0));
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

VOID HLightAndNormalViewItem::Unload() {

}

VOID HLightAndNormalViewItem::Show() {

}

VOID HLightAndNormalViewItem::Hide() {

}

VOID HLightAndNormalViewItem::Update() {

}
