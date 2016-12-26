#include "GameViewObject.h"

#include "program.h"
#include "Common/CommonCode.h"
#include "CoordinateAxisViewItem.h"
#include "PrismaticViewItem.h"
#include "LightMaterialAndNormalViewItem.h"
#include "TextureViewItem.h"
#include <string>

using namespace std;

extern HProgram *g_program;
extern string HGameEventStr_PROGRAM_SIZE;
extern string HGameEventStr_PROGRAM_MOVE;

//--------分界线-----------------------------------------------------------------
VOID HIGameViewItem::Load() {

}

VOID HIGameViewItem::Unload() {

}

VOID HIGameViewItem::Show() {

}

VOID HIGameViewItem::Hide() {

}

VOID HIGameViewItem::Update() {

}

//--------分界线-----------------------------------------------------------------
VOID HGameViewObject::CalculationCameraLocation() {
	D3DXMatrixTranslation(&m_camera, m_cameraX, m_cameraY, m_cameraZ);
	D3DXMATRIX ry;
	D3DXMatrixRotationY(&ry, m_cameraRY);
	D3DXMATRIX rx;
	D3DXMatrixRotationX(&rx, m_cameraRX);
	m_camera = m_camera * ry * rx;
}

VOID HGameViewObject::Load() {
	POINT const *center = g_program->Get_m_center();
	m_device = g_program->Get_m_device();

	CalculationCameraLocation();

	m_coordinateAxix = new HCoordinateAxisViewItem();
	m_coordinateAxix->Load();

	m_prismatic = new HPrismaticViewItem();
	m_prismatic->Load();

	m_lightMaterialAndNormal = new HLightMaterialAndNormalViewItem();
	m_lightMaterialAndNormal->Load();

	m_texture = new HTextureViewItem();
	m_texture->Load();
}

VOID HGameViewObject::Unload() {
	m_texture->Unload();
	SAFEDELETENULL(m_texture);

	m_lightMaterialAndNormal->Unload();
	SAFEDELETENULL(m_lightMaterialAndNormal);

	m_prismatic->Unload();
	SAFEDELETENULL(m_prismatic);

	m_coordinateAxix->Unload();
	SAFEDELETENULL(m_coordinateAxix);
}

VOID HGameViewObject::Show() {
	INT w = g_program->Get_m_width();
	INT h = g_program->Get_m_height();
	D3DXMATRIX pf;
	D3DXMatrixPerspectiveFovLH(
		&pf,
		D3DX_PI * 0.33f,
		(FLOAT)w / (FLOAT)h,
		0.0f,
		1000.0f
	);
	m_device->SetTransform(D3DTS_PROJECTION, &pf);

	m_coordinateAxix->Show();
	m_prismatic->Show();
	m_lightMaterialAndNormal->Show();
	m_texture->Show();
}

VOID HGameViewObject::Hide() {
	m_texture->Hide();
	m_lightMaterialAndNormal->Hide();
	m_prismatic->Hide();
	m_coordinateAxix->Hide();
}

VOID HGameViewObject::OnGetFocus() {
	g_program->Get_m_InputEventMgr()->Subscribe(this, InputEventType_MA);
	g_program->Get_m_InputEventMgr()->Subscribe(this, (InputEventType)DIK_W);
	g_program->Get_m_InputEventMgr()->Subscribe(this, (InputEventType)DIK_A);
	g_program->Get_m_InputEventMgr()->Subscribe(this, (InputEventType)DIK_S);
	g_program->Get_m_InputEventMgr()->Subscribe(this, (InputEventType)DIK_D);
	g_program->Get_m_InputEventMgr()->Subscribe(this, (InputEventType)DIK_SPACE);
	g_program->Get_m_InputEventMgr()->Subscribe(this, (InputEventType)DIK_LSHIFT);
}

VOID HGameViewObject::OnLostFocus() {
	g_program->Get_m_InputEventMgr()->Unsubscribe(this, (InputEventType)DIK_LSHIFT);
	g_program->Get_m_InputEventMgr()->Unsubscribe(this, (InputEventType)DIK_SPACE);
	g_program->Get_m_InputEventMgr()->Unsubscribe(this, (InputEventType)DIK_D);
	g_program->Get_m_InputEventMgr()->Unsubscribe(this, (InputEventType)DIK_S);
	g_program->Get_m_InputEventMgr()->Unsubscribe(this, (InputEventType)DIK_A);
	g_program->Get_m_InputEventMgr()->Unsubscribe(this, (InputEventType)DIK_W);
	g_program->Get_m_InputEventMgr()->Unsubscribe(this, InputEventType_MA);
}

VOID HGameViewObject::Update() {
	m_device->SetTransform(D3DTS_VIEW, &m_camera);
	m_coordinateAxix->Update();
	m_prismatic->Update();
	m_lightMaterialAndNormal->Update();
	m_texture->Update();
}

BOOL HGameViewObject::OnMessage(InputEventType key, DOUBLE durationTime, LONG const *distance, INT distanceCount) {
	switch (key) {
	case InputEventType_MA:
	{
		if (distanceCount < 2) {
			return FALSE;
		}

		FLOAT changeValueRY = 0 - distance[0] * m_cameraRSpeed;
		FLOAT changeValueRX = 0 - distance[1] * m_cameraRSpeed;
		m_cameraRY = m_cameraRY + changeValueRY;
		m_cameraRX = m_cameraRX + changeValueRX;
		if (m_cameraRX > (0.5 * D3DX_PI)) {
			m_cameraRX = 0.5 * D3DX_PI;
		}
		if (m_cameraRX < (- 0.5 * D3DX_PI)) {
			m_cameraRX = -0.5 * D3DX_PI;
		}
		CalculationCameraLocation();
		return TRUE;
	}break;
	case DIK_W:
	{
		FLOAT changeValue = (FLOAT)durationTime * m_cameraMSpeed;
		m_cameraZ = m_cameraZ - changeValue;
		CalculationCameraLocation();
		return TRUE;
	}break;
	case DIK_S:
	{
		FLOAT changeValue = (FLOAT)durationTime * m_cameraMSpeed;
		m_cameraZ = m_cameraZ + changeValue;
		CalculationCameraLocation();
		return TRUE;
	}break;
	case DIK_A:
	{
		FLOAT changeValue = (FLOAT)durationTime * m_cameraMSpeed;
		m_cameraX = m_cameraX + changeValue;
		CalculationCameraLocation();
		return TRUE;
	}break;
	case DIK_D:
	{
		FLOAT changeValue = (FLOAT)durationTime * m_cameraMSpeed;
		m_cameraX = m_cameraX - changeValue;
		CalculationCameraLocation();
		return TRUE;
	}break;
	case DIK_SPACE:
	{
		FLOAT changeValue = (FLOAT)durationTime * m_cameraMSpeed;
		m_cameraY = m_cameraY - changeValue;
		CalculationCameraLocation();
		return TRUE;
	}break;
	case DIK_LSHIFT:
	{
		FLOAT changeValue = (FLOAT)durationTime * m_cameraMSpeed;
		m_cameraY = m_cameraY + changeValue;
		CalculationCameraLocation();
		return TRUE;
	}break;
	}

	return FALSE;
}
