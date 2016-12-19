#include "InputEventMgr.h"

//--------·Ö½çÏß-----------------------------------------------------------------
BOOL HInputEventMgr::Create() {
	INT i;
	size_t eventCount = InputEventType_MAX;
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

VOID HInputEventMgr::Subscribe(HIInputEventReceiver *receiver, InputEventType key) {
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

VOID HInputEventMgr::Unsubscribe(HIInputEventReceiver *receiver, InputEventType key) {
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

BOOL HInputEventMgr::FireEvent(InputEventType key, DOUBLE durationTime, LONG const *distance, INT distanceCount) {
	BOOL isDealed = FALSE;

	M_RL *rl = m_kv.at(key);
	M_RL::iterator it = rl->begin();
	while (it != rl->end()) {
		if ((*it)->OnMessage(key, durationTime, distance, distanceCount) == TRUE) {
			isDealed = TRUE;
		}
		it++;
	}

	return isDealed;
}
