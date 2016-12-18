#include "CommonCode.h"

#include <stdlib.h>

//--------·Ö½çÏß-----------------------------------------------------------------
HXYZCVertex::HXYZCVertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color)
	:m_x(x), m_y(y), m_z(z), m_color(color) {
}

CHAR* WC2C(WCHAR const *in) {
	int CHAR_LEN = WideCharToMultiByte(CP_ACP, 0, in, -1, NULL, 0, NULL, NULL);
	if (CHAR_LEN == 0) {
		return NULL;
	}
	CHAR *out = (CHAR*)malloc(CHAR_LEN * sizeof(CHAR));
	WideCharToMultiByte(CP_ACP, 0, in, -1, out, CHAR_LEN, NULL, NULL);
	return out;
}

WCHAR* C2WC(CHAR const *in) {
	int WCHAR_LEN = MultiByteToWideChar(CP_ACP, 0, in, -1, NULL, 0);
	if (WCHAR_LEN == 0) {
		return NULL;
	}
	WCHAR *out = (WCHAR*)malloc(WCHAR_LEN * sizeof(WCHAR));
	MultiByteToWideChar(CP_ACP, 0, in, -1, out, WCHAR_LEN);
	return out;
}
