#include "GameViewObject.h"

#include "program.h"
#include "Common/CommonCode.h"
#include "CoordinateAxisViewItem.h"
#include "PrismaticViewItem.h"
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
VOID HGameViewObject::Load() {
	POINT const *center = g_program->Get_m_center();
	m_device = g_program->Get_m_device();

	m_coordinateAxix = new HCoordinateAxisViewItem();
	m_coordinateAxix->Load();

	m_prismatic = new HPrismaticViewItem();
	m_prismatic->Load();
}

VOID HGameViewObject::Unload() {
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

	D3DXMatrixLookAtLH(&m_cameraLocate, &D3DXVECTOR3(5.0f, 5.0f, -3.0f), &D3DXVECTOR3(0.0f, 0.0f, 1.0f), &D3DXVECTOR3(0.0f, 1.0f, 0.0f));

	m_coordinateAxix->Show();
	m_prismatic->Show();
}

VOID HGameViewObject::Hide() {
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
	m_device->SetTransform(D3DTS_VIEW, &m_cameraLocate);
	m_coordinateAxix->Update();
	m_prismatic->Update();
}

BOOL HGameViewObject::OnMessage(InputEventType key, DOUBLE durationTime, LONG const *distance, INT distanceCount) {
	switch (key) {
	case InputEventType_MA:
	{
		                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
	}break;
	case DIK_W:
	{
	}break;
	case DIK_A:
	{
	}break;
	case DIK_S:
	{
	}break;
	case DIK_D:
	{
	}break;
	case DIK_SPACE:
	{
	}break;
	case DIK_LSHIFT:
	{
	}break;
	}

	return FALSE;
}
