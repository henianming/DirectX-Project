#pragma once

#include <Windows.h>
#include <d3d9.h>

#define ERROR_OUT() \
do{ \
	printf("%s\n%s\n%s\n", __FILE__, __FUNCTION__, __LINE__); \
}while(0) \

#define SAFEDELETE(a) \
do{ \
	if (a) { \
		delete (a); \
	} \
}while(0) \

#define SAFEDELETENULL(a) \
do{ \
	if (a) { \
		delete (a); \
		(a) = NULL; \
	} \
}while(0) \

#define UNUSED(a) ((VOID)(a))

#define R_FAILED(A) \
do { \
	if (!A) { \
		ERROR_OUT(); \
		return; \
	} \
} while(0) \

#define RF_FAILED(A) \
do { \
	if (!A) { \
		ERROR_OUT(); \
		return FALSE; \
	} \
} while(0) \

#define R_NULL(A) \
do { \
	if ((A) == NULL) { \
		ERROR_OUT(); \
		return; \
	} \
} while(0) \

#define RF_NULL(A) \
do { \
	if ((A) == NULL) { \
		ERROR_OUT(); \
		return FALSE; \
	} \
} while(0) \

#define R_HR_FAILED(A) \
do { \
	if (FAILED(A)) { \
		ERROR_OUT(); \
		return; \
	} \
} while(0) \

#define RF_HR_FAILED(A) \
do { \
	if (FAILED(A)) { \
		ERROR_OUT(); \
		return FALSE; \
	} \
} while(0) \

#define IS_IN_RANGE_LN_HN(S, L, H) ((S) > (L) && (S) < (H)) ? TRUE : FALSE
#define IS_IN_RANGE_LE_HE(S, L, H) ((S) >= (L) && (S) <= (H)) ? TRUE : FALSE
#define IS_IN_RANGE_LE_HN(S, L, H) ((S) >= (L) && (S) < (H)) ? TRUE : FALSE
#define IS_IN_RANGE_LN_HE(S, L, H) ((S) > (L) && (S) <= (H)) ? TRUE : FALSE

#define ABS(N) ((N) > 0) ? N : (0 - N)

CHAR* WC2C(WCHAR const *in);
WCHAR* C2WC(CHAR const *in);

//--------分界线-----------------------------------------------------------------
class HXYZCVertex {
public:
	static DWORD const FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE;

public:
	FLOAT m_x, m_y, m_z;
	D3DCOLOR m_color;

public:
	HXYZCVertex(FLOAT x, FLOAT y, FLOAT z, D3DCOLOR color);
};

//--------分界线-----------------------------------------------------------------
class HXYZNVertex {
public:
	static DWORD const FVF = D3DFVF_XYZ | D3DFVF_NORMAL;

public:
	FLOAT m_x, m_y, m_z;
	FLOAT m_nx, m_ny, m_nz;

public:
	HXYZNVertex(FLOAT x, FLOAT y, FLOAT z, FLOAT nx, FLOAT ny, FLOAT nz);
};