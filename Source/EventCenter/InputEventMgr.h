#pragma once

#include <Windows.h>
#include <vector>
#include <list>

#define KB_EVENT_IDX 256
#define MA_EVENT_IDX KB_EVENT_IDX + 1
#define MB_EVENT_IDX MA_EVENT_IDX + 5

enum InputEventType {
	//keyboard
	InputEventType_Keyboard = 255,
	//mouse axis
	InputEventType_MA,
	//mouse 8 botton
	InputEventType_LMB,
	InputEventType_RMB,
	InputEventType_MMB,
	InputEventType_CMB1,
	InputEventType_CMB2,
	InputEventType_CMB3,
	InputEventType_CMB4,
	InputEventType_CMB5,
	InputEventType_MAX,
};

//--------分界线-----------------------------------------------------------------
class HIInputEventReceiver {
public:
	virtual BOOL OnMessage(InputEventType key, DOUBLE durationTime, LONG const *distance, INT distanceCount) = 0;
};

//--------分界线-----------------------------------------------------------------
class HInputEventMgr {
private:
	typedef std::list<HIInputEventReceiver*> M_RL;
	typedef std::vector<M_RL*> M_KV;

private:
	M_KV m_kv;

public:
	BOOL Create();
	BOOL Release();

	VOID Subscribe(HIInputEventReceiver *receiver, InputEventType key);
	VOID Unsubscribe(HIInputEventReceiver *receiver, InputEventType key);
	BOOL FireEvent(InputEventType key, DOUBLE durationTime, LONG const *distance, INT distanceCount);
};