#include "TextureViewItem.h"

#include "program.h"
#include "Common/CommonCode.h"

extern HProgram *g_program;

VOID HTextureViewItem::Sence() {
	R_HR_FAILED(m_device->BeginScene());
	{
		R_HR_FAILED(m_device->SetStreamSource(0, m_vertexBuf, 0, sizeof(HXYZNTVertex)));
		R_HR_FAILED(m_device->SetFVF(HXYZNTVertex::FVF));
		R_HR_FAILED(m_device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2));
	}
	R_HR_FAILED(m_device->EndScene());
}

VOID HTextureViewItem::Load() {
	m_device = g_program->Get_m_device();
	R_NULL(m_device);

	D3DXMatrixTranslation(&m_worldPos, -4.0f, 0.0f, 0.0f);

	R_HR_FAILED(
		D3DXCreateTextureFromFile(m_device, L"Resources\\crafting_table_top.png", &m_texture_top)
	);
	R_HR_FAILED(
		D3DXCreateTextureFromFile(m_device, L"Resources\\crafting_table_bottom.png", &m_texture_bottom)
	);
	R_HR_FAILED(
		D3DXCreateTextureFromFile(m_device, L"Resources\\crafting_table_front.png", &m_texture_front)
	);
	R_HR_FAILED(
		D3DXCreateTextureFromFile(m_device, L"Resources\\crafting_table_side.png", &m_texture_side)
	);
}

VOID HTextureViewItem::Unload() {

}

VOID HTextureViewItem::Show() {
	R_HR_FAILED(
		m_device->CreateVertexBuffer(
			6 * sizeof(HXYZNTVertex),
			D3DUSAGE_WRITEONLY,
			HXYZNTVertex::FVF,
			D3DPOOL_MANAGED,
			&m_vertexBuf,
			0
		)
	);
	HXYZNTVertex *vertexBuf;
	R_HR_FAILED(m_vertexBuf->Lock(0, 0, (VOID**)(&vertexBuf), 0));
	{
		int i = 0;
		vertexBuf[i++] = HXYZNTVertex(-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f);
		vertexBuf[i++] = HXYZNTVertex(1.0f, 1.0f, -1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f);
		vertexBuf[i++] = HXYZNTVertex(1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f);

		vertexBuf[i++] = HXYZNTVertex(-1.0f, 1.0f, -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f);
		vertexBuf[i++] = HXYZNTVertex(1.0f, -1.0f, -1.0f, 1.0f, -1.0f, -1.0f, 1.0f, 1.0f);
		vertexBuf[i++] = HXYZNTVertex(-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 1.0f);
	}
	R_HR_FAILED(m_vertexBuf->Unlock());

	R_HR_FAILED(
		m_device->CreateVertexBuffer(
			1 * sizeof(HXYZCVertex),
			D3DUSAGE_WRITEONLY,
			HXYZCVertex::FVF,
			D3DPOOL_MANAGED,
			&m_dotVertexBuf,
			0
		)
	);
	HXYZCVertex *dotBuf;
	R_HR_FAILED(m_dotVertexBuf->Lock(0, 0, (VOID**)(&dotBuf), 0));
	{
		dotBuf[0] = HXYZCVertex(0.0f, 0.0f, 0.0f, D3DCOLOR_XRGB(255, 0, 0));
	}
	R_HR_FAILED(m_dotVertexBuf->Unlock());
}

VOID HTextureViewItem::Hide() {

}

VOID HTextureViewItem::Update() {
	R_HR_FAILED(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	R_HR_FAILED(m_device->SetRenderState(D3DRS_LIGHTING, FALSE));

	R_HR_FAILED(m_device->SetTransform(D3DTS_WORLD, &m_worldPos));

	R_HR_FAILED(m_device->BeginScene());
	{
		m_device->SetStreamSource(0, m_dotVertexBuf, 0, sizeof(HXYZCVertex));
		m_device->SetFVF(HXYZCVertex::FVF);
		m_device->DrawPrimitive(D3DPT_POINTLIST, 0, 1);
	}
	R_HR_FAILED(m_device->EndScene());

	R_HR_FAILED(m_device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID));
	R_HR_FAILED(m_device->SetRenderState(D3DRS_LIGHTING, TRUE));

	D3DXMATRIX temp;
	D3DXMATRIX worldTemp;

	static FLOAT angle = 0.0f;
	D3DXMatrixRotationY(&temp, 0.0f * D3DX_PI);
	angle += 0.00004f;
	if (angle >= 2.0f) {
		angle = 0.0f;
	}
	worldTemp = temp * m_worldPos;
	R_HR_FAILED(m_device->SetTransform(D3DTS_WORLD, &worldTemp));
	R_HR_FAILED(m_device->SetTexture(0, m_texture_front));
	Sence();
	
	D3DXMatrixRotationY(&temp, 0.5f * D3DX_PI);
	worldTemp = temp * m_worldPos;
	R_HR_FAILED(m_device->SetTransform(D3DTS_WORLD, &worldTemp));
	R_HR_FAILED(m_device->SetTexture(0, m_texture_side));
	Sence();
	
	D3DXMatrixRotationY(&temp, 1.0f * D3DX_PI);
	worldTemp = temp * m_worldPos;
	R_HR_FAILED(m_device->SetTransform(D3DTS_WORLD, &worldTemp));
	R_HR_FAILED(m_device->SetTexture(0, m_texture_side));
	Sence();
	
	D3DXMatrixRotationY(&temp, 1.5f * D3DX_PI);
	worldTemp = temp * m_worldPos;
	R_HR_FAILED(m_device->SetTransform(D3DTS_WORLD, &worldTemp));
	R_HR_FAILED(m_device->SetTexture(0, m_texture_side));
	Sence();
	/*
	D3DXMatrixRotationX(&temp, 0.5f * D3DX_PI);
	worldTemp = temp * m_worldPos;
	R_HR_FAILED(m_device->SetTransform(D3DTS_WORLD, &worldTemp));
	R_HR_FAILED(m_device->SetTexture(0, m_texture_top));
	Sence();

	D3DXMatrixRotationX(&temp, -0.5f * D3DX_PI);
	worldTemp = temp * m_worldPos;
	R_HR_FAILED(m_device->SetTransform(D3DTS_WORLD, &worldTemp));
	R_HR_FAILED(m_device->SetTexture(0, m_texture_bottom));
	Sence();
	*/
	R_HR_FAILED(m_device->SetTexture(0, NULL));
}
