#pragma once

#include "../ViewObjectMgr.h"
#include "EventCenter/WndProcEventMgr.h"
#include "EventCenter/GameEventMgr.h"
#include "EventCenter/InputEventMgr.h"
#include "TimerCenter/Timer.h"

//--------分界线-----------------------------------------------------------------
class HIGameViewItem {
public:
	virtual VOID Load();
	virtual VOID Unload();
	virtual VOID Show();
	virtual VOID Hide();
	virtual VOID Update();
};

//--------分界线-----------------------------------------------------------------
class HGameViewObject : public HIViewObject, public HIInputEventReceiver {
private:
	IDirect3DDevice9 *m_device;

	D3DXMATRIX m_cameraLocate;
	FLOAT const m_cameraMSpeed = 1.0f;
	FLOAT const m_cameraRSpeed = (FLOAT)1 / (FLOAT)360 * D3DX_PI;

	HIGameViewItem *m_coordinateAxix;
	HIGameViewItem *m_prismatic;

public:
	virtual VOID Load();
	virtual VOID Unload();
	virtual VOID Show();
	virtual VOID Hide();
	virtual VOID OnGetFocus();
	virtual VOID OnLostFocus();
	virtual VOID Update();

public:
	virtual BOOL OnMessage(InputEventType key, DOUBLE durationTime, LONG const *distance, INT distanceCount);
};