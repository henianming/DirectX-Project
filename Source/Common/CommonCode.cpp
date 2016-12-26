#include "CommonCode.h"

#include <stdlib.h>

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

//--------分界线-----------------------------------------------------------------
HXYZCVertex::HXYZCVertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color)
	:m_x(x), m_y(y), m_z(z), m_color(color) {
}

//--------分界线-----------------------------------------------------------------
HXYZNVertex::HXYZNVertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz)
	: m_x(x), m_y(y), m_z(z), m_nx(nx), m_ny(ny), m_nz(nz) {
}

HXYZNTVertex::HXYZNTVertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz, FLOAT u, FLOAT v)
	: m_x(x), m_y(y), m_z(z), m_nx(nx), m_ny(ny), m_nz(nz), m_u(u), m_v(v) {
}
