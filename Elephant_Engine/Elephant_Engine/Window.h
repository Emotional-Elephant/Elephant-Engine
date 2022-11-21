#pragma once
#include "Singleton.h"
#include <windows.h>

class Window : public Singleton<Window>
{
	friend class Singleton<Window>;
private:
	HINSTANCE			hinstance_;
	HWND				hwnd_;
	RECT				rt_window_;
	RECT				rt_client_;
	DWORD				cs_style_;
public:
	HINSTANCE			GetHInstance() const { return hinstance_; }
	HWND				GetHWindow() const { return hwnd_; }
	RECT				GetRTWindow() const { return rt_window_; }
	RECT				GetRTClient() const { return rt_client_; }
	DWORD				GetCSStyle() const { return cs_style_; }
public:
	bool				SetWindow(HINSTANCE hinstance, const WCHAR* title, UINT width = 1024, UINT height = 768);
	ATOM				RegisterWNDClass();
	BOOL				InitInstance(const WCHAR* title, UINT width, UINT height);
	bool				Run();
	void				CenterWindow();
public:
	virtual bool		Init();
	virtual bool		Frame();
	virtual bool		Render();
	virtual bool		Release();
	virtual LRESULT		MsgProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
private:
	Window() {};
	~Window() = default;
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};
#define I_Window Window::GetInstance()