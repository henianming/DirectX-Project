#include "InputEventMgr.h"

#define KB_EVENT_COUNT 256
#define MA_EVENT_COUNT 1
#define MB_EVENT_COUNT 5

BOOL HInputEventMgr::Create() {
	INT i;
	size_t eventCount = KB_EVENT_COUNT + MA_EVENT_COUNT + MB_EVENT_COUNT;
	m_kv.reserve(eventCount);
	for (i = 0; i < eventCount; i++) {
		m_kv.push_back(new M_RL());
	}

	return TRUE;
}

BOOL HInputEventMgr::Release() {
	M_KV::iterator it = m_kv.begin();
	while (it != m_kv.end()) {
		delete *it;

		it++;
	}
	m_kv.clear();

	return TRUE;
}

VOID HInputEventMgr::Subscribe(HIInputEventReceiver *receiver, BYTE key) {
	M_RL *rl = m_kv.at(key);
	M_RL::iterator it = rl->begin();
	while (it != rl->end()) {
		if ((INT)(*it) == (INT)receiver) {
			return;
		}

		it++;
	}

	m_kv.at(key)->push_back(receiver);
}

VOID HInputEventMgr::Unsubscribe(HIInputEventReceiver *receiver, BYTE key) {
	M_RL *rl = m_kv.at(key);
	M_RL::reverse_iterator rit = rl->rbegin();
	while (rit != rl->rend()) {
		if ((INT)(*rit) == (INT)receiver) {
			rl->erase((++rit).base());
			return;
		}

		rit++;
	}
}

BOOL HInputEventMgr::FireEvent(BYTE key, DOUBLE durationTime, LONG distance) {
	BOOL isDealed = FALSE;

	M_RL *rl = m_kv.at(key);
	M_RL::iterator it = rl->begin();
	while (it != rl->end()) {
		if ((*it)->OnMessage(key, durationTime, distance) == TRUE) {
			isDealed = TRUE;
		}
		it++;
	}

	return isDealed;
}
