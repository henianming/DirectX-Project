#pragma once

#include <Windows.h>
#include <dinput.h>
#include <vector>
#include <list>

//--------分界线-----------------------------------------------------------------
class HIInputEventReceiver {
public:
	virtual BOOL OnMessage(BYTE key, DOUBLE durationTime, LONG distance) = 0;
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

	VOID Subscribe(HIInputEventReceiver *receiver, BYTE key);
	VOID Unsubscribe(HIInputEventReceiver *receiver, BYTE key);
	BOOL FireEvent(BYTE key, DOUBLE durationTime, LONG distance);
};