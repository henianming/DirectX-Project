#include "program.h"
#include "Common/CommonCode.h"
#include RESOURCE_H_PATH
#include <string>
using namespace std;

extern string HGameEventStr_PROGRAM_SIZE;
extern string HGameEventStr_PROGRAM_MOVE;

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#define DESKTOP_W 1920
#define DESKTOP_H 1080
#define PROGRAM_W 800
#define PROGRAM_H 600

//--------分界线-----------------------------------------------------------------
BOOL HProgram::Create(HINSTANCE hInstance, INT showType) {
	//处理输入的参数
	m_hInstance = hInstance;
	m_showType = showType;

	//初始化模块
	//事件相关
	RF_FAILED(m_wndProcEventMgr.Create());

	RF_FAILED(m_gameEventMgr.Create());

	RF_FAILED(m_InputEventMgr.Create());
	//统一订阅
	SubscribeEvent();

	RF_FAILED(CreateWnd());

	RF_FAILED(CreateDirectX());

	RF_FAILED(m_inputDeviceMgr.Create());

	RF_FAILED(m_timeMgr.Create());

	RegisteTime();

	RF_FAILED(m_timerMgr.Create());

	RegisteTimer();

	RF_FAILED(m_viewObjectMgr.Create());

	//初始化数据
	m_count = 0;

	GetWindowRect(m_hWnd, &m_rect);
	CalculateSize();
	CalculateCenter();

	return TRUE;
}

BOOL HProgram::Release() {
	RF_FAILED(m_viewObjectMgr.Release());

	UnregisteTimer();

	RF_FAILED(m_timerMgr.Release());

	UnregisteTime();

	RF_FAILED(m_timeMgr.Release());

	RF_FAILED(m_inputDeviceMgr.Release());

	RF_FAILED(ReleaseDirectX());

	RF_FAILED(ReleaseWnd());

	UnsubscribeEvent();

	RF_FAILED(m_InputEventMgr.Release());

	RF_FAILED(m_gameEventMgr.Release());

	RF_FAILED(m_wndProcEventMgr.Release());

	return TRUE;
}

BOOL HProgram::Update() {
	m_count++;

	m_timeMgr.Update();
	
	m_timerMgr.Update();

	m_inputDeviceMgr.Update();

	m_viewObjectMgr.Update();
	
	return TRUE;
}

HWND HProgram::Get_m_hWnd() {
	return m_hWnd;
}

IDirect3DDevice9* HProgram::Get_m_device() {
	return m_device;
}

HTimeMgr* HProgram::Get_m_timeMgr() {
	return &m_timeMgr;
}

HTime* HProgram::Get_m_time() {
	return &m_time;
}

HTimerMgr* HProgram::Get_m_timerMgr() {
	return &m_timerMgr;
}

RECT const* HProgram::Get_m_rect() {
	return &m_rect;
}

LONG HProgram::Get_m_width() {
	return m_width;
}

LONG HProgram::Get_m_height() {
	return m_height;
}

POINT const* HProgram::Get_m_center() {
	return &m_center;
}

HWndProcEventMgr* HProgram::Get_m_wndProcEventMgr() {
	return &m_wndProcEventMgr;
}

HGameEventMgr* HProgram::Get_m_gameEventMgr() {
	return &m_gameEventMgr;
}


HInputEventMgr* HProgram::Get_m_InputEventMgr() {
	return &m_InputEventMgr;
}

HINSTANCE HProgram::Get_m_hInstance() {
	return m_hInstance;
}

VOID HProgram::InitWndClass() {
	m_wndClass.cbClsExtra = 0;
	m_wndClass.cbWndExtra = 0;
	m_wndClass.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
	m_wndClass.hCursor = LoadCursor(0, IDC_ARROW);
	m_wndClass.hIcon = LoadIcon(m_hInstance, (LPCWSTR)RES_ICO_TILTE);
	m_wndClass.hInstance = m_hInstance;
	m_wndClass.lpfnWndProc = WndProc;
	m_wndClass.lpszClassName = L"DirectX Program Class";
	m_wndClass.lpszMenuName = NULL;
	m_wndClass.style = CS_HREDRAW | CS_VREDRAW;
}

BOOL HProgram::CreateWnd() {
	InitWndClass();

	RegisterClass(&m_wndClass);

	m_hWnd = CreateWindow(
		m_wndClass.lpszClassName, L"",
		WS_OVERLAPPEDWINDOW,
		(DESKTOP_W - PROGRAM_W) / 2, (DESKTOP_H - PROGRAM_H) / 2, PROGRAM_W, PROGRAM_H,
		0, 0, m_wndClass.hInstance, 0
	);
	if (m_hWnd == 0) {
		return FALSE;
	}

	ShowWindow(m_hWnd, m_showType);

	return TRUE;
}

BOOL HProgram::ReleaseWnd() {
	UnregisterClass(m_wndClass.lpszClassName, m_wndClass.hInstance);

	return TRUE;
}

VOID HProgram::InitDirectPresentParameters() {
	m_d3dPresentParameters.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_d3dPresentParameters.BackBufferCount = 2;
	m_d3dPresentParameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	m_d3dPresentParameters.BackBufferHeight = Get_m_height();
	m_d3dPresentParameters.BackBufferWidth = Get_m_width();
	m_d3dPresentParameters.EnableAutoDepthStencil = TRUE;
	m_d3dPresentParameters.Flags = 0;
	m_d3dPresentParameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_d3dPresentParameters.hDeviceWindow = m_hWnd;
	m_d3dPresentParameters.MultiSampleQuality = 0;
	m_d3dPresentParameters.MultiSampleType = D3DMULTISAMPLE_8_SAMPLES;
	m_d3dPresentParameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	m_d3dPresentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_d3dPresentParameters.Windowed = TRUE;
}

BOOL HProgram::CreateDirectX() {
	HRESULT hResult;

	m_iDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_iDirect3D9 == NULL) {
		return FALSE;
	};

	InitDirectPresentParameters();

	D3DCAPS9 d3dCaps9;
	hResult = m_iDirect3D9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &d3dCaps9);
	if (FAILED(hResult)) {
		return FALSE;
	}
	DWORD behaviorFlags;
	if (d3dCaps9.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
		behaviorFlags = D3DCREATE_HARDWARE_VERTEXPROCESSING;
	} else {
		behaviorFlags = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
	}

	hResult = m_iDirect3D9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, behaviorFlags, &m_d3dPresentParameters, &m_device);
	if (FAILED(hResult)) {
		return FALSE;
	}

	return TRUE;
}

BOOL HProgram::ReleaseDirectX() {
	if (m_device) {
		m_device->Release();
		m_device = NULL;
	}

	if (m_iDirect3D9) {
		m_iDirect3D9->Release();
		m_iDirect3D9 = NULL;
	}

	return TRUE;
}

VOID HProgram::SubscribeEvent() {
	m_wndProcEventMgr.Subscribe(this, HWndProcEventType_MOVE);
	m_wndProcEventMgr.Subscribe(this, HWndProcEventType_SIZE);

	m_InputEventMgr.Subscribe(this, DIK_ESCAPE);
}

VOID HProgram::UnsubscribeEvent() {
	m_InputEventMgr.Unsubscribe(this, DIK_ESCAPE);

	m_wndProcEventMgr.Unsubscribe(this, HWndProcEventType_SIZE);
	m_wndProcEventMgr.Unsubscribe(this, HWndProcEventType_MOVE);
}

VOID HProgram::RegisteTime() {
	m_timeMgr.Registe(&m_time);
}

VOID HProgram::UnregisteTime() {
	m_timeMgr.Unregiste(&m_time);
}

VOID HProgram::RegisteTimer() {
	m_timerMgr.Registe(this, 1, m_fpsRefreshIntervalSec, &m_time);
}

VOID HProgram::UnregisteTimer() {
	m_timerMgr.Unregiste(this, 1);
}
 
VOID HProgram::UpdataFps() {
	m_fps = (DOUBLE)m_count / (DOUBLE)m_fpsRefreshIntervalSec;
}

VOID HProgram::TitleView() {
	wchar_t wc[256];
	swprintf(wc, 256, L"DirectX Program Window       fps->%lf", m_fps);
	SetWindowText(m_hWnd, wc);
}

VOID HProgram::CalculateSize() {
	m_width = m_rect.right - m_rect.left;
	m_height = m_rect.bottom - m_rect.top;
}

VOID HProgram::CalculateCenter() {
	m_center.x = (m_rect.right + m_rect.left) / 2;
	m_center.y = (m_rect.bottom + m_rect.top) / 2;
}

BOOL HProgram::OnMessage(HWndProcEventType eventType, WPARAM wParam, LPARAM lParam) {
	switch (eventType) {
	case HWndProcEventType_MOVE:
	{
		GetWindowRect(m_hWnd, &m_rect);
		CalculateCenter();
		m_gameEventMgr.FireEvent(&HGameEventStr_PROGRAM_MOVE, NULL);
	}break;
	case HWndProcEventType_SIZE:
	{
		GetWindowRect(m_hWnd, &m_rect);
		CalculateSize();
		CalculateCenter();
		m_gameEventMgr.FireEvent(&HGameEventStr_PROGRAM_SIZE, NULL);
	}break;
	}

	return FALSE;
}


BOOL HProgram::OnMessage(BYTE key, DOUBLE durationTime, LONG distance) {
	switch (key) {
	case DIK_ESCAPE:
	{
		DestroyWindow(m_hWnd);
	}break;
	}

	return FALSE;
}

VOID HProgram::OnTimer(INT id) {
	switch (id) {
	case 1:
	{
		UpdataFps();
		TitleView();
		m_count = 0;
	}break;
	}
}