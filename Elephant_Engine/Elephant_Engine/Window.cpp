#include "Window.h"

LRESULT CALLBACK WndProc(
	HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	return I_Window.MsgProc(hWnd, message, wParam, lParam);
}

bool Window::SetWindow(HINSTANCE hinstance, const WCHAR* title, UINT width, UINT height)
{
	hinstance_ = hinstance;
	WORD ret = RegisterWNDClass();

	return (!InitInstance(title, width, height)) ? false : true;
}

ATOM Window::RegisterWNDClass()
{
	WNDCLASSEXW wcex;
	ZeroMemory(&wcex, sizeof(WNDCLASSEX));

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.hInstance = hinstance_;
	wcex.hbrBackground = CreateSolidBrush(RGB(7, 77, 7));
	wcex.lpszClassName = L"Elephent-Engine";
	wcex.lpfnWndProc = WndProc;
	wcex.hCursor = LoadCursor(nullptr, IDC_UPARROW);
	return RegisterClassEx(&wcex);;
}

BOOL Window::InitInstance(const WCHAR* title, UINT width, UINT height)
{
	cs_style_ = WS_OVERLAPPEDWINDOW;

	RECT rc = { 0, 0, width, height };
	AdjustWindowRect(&rc, cs_style_, FALSE);

	hwnd_ = CreateWindowW(
		L"Elephent-Engine",
		title,
		cs_style_,
		0, 0,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr, nullptr,
		hinstance_, nullptr);

	if (!hwnd_) return FALSE;
	ShowWindow(hwnd_, SW_SHOW);

	GetWindowRect(hwnd_, &rt_window_);
	GetClientRect(hwnd_, &rt_client_);

	return TRUE;
}

bool Window::Run()
{
	MSG msg = { 0, };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			return true;
		}
	}
	return false;
}

void Window::CenterWindow()
{
	UINT iScreenWidht = GetSystemMetrics(SM_CXFULLSCREEN);
	UINT iScreenHieght = GetSystemMetrics(SM_CYFULLSCREEN);
	UINT cx, cy;
	cx = (iScreenWidht - (rt_window_.right - rt_window_.left)) * 0.5f;
	cy = (iScreenHieght - (rt_window_.bottom - rt_window_.top)) * 0.5f;
	MoveWindow(hwnd_, cx, cy,
		rt_window_.right - rt_window_.left,
		rt_window_.bottom - rt_window_.top,
		true);
}

bool Window::Init()
{
	return true;
}

bool Window::Frame()
{
	return true;
}

bool Window::Render()
{
	return true;
}

bool Window::Release()
{
	return true;
}

LRESULT Window::MsgProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return  DefWindowProc(hwnd, message, wparam, lparam);
}
