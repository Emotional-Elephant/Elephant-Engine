#include "Sample.h"

#define WINDOW_SIZE_X 1024
#define WINDOW_SIZE_Y 768
#define WINDOW_NAME L"DirectXGameEngine"

int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPWSTR		lpCmdLine,
	int			nCmdShow) {

	I_Window.SetWindow(hInstance, WINDOW_NAME, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	Sample sample;
	sample.Run();

	return 0;
}

bool Sample::Init()
{
	return false;
}

bool Sample::Frame()
{
	return false;
}

bool Sample::Render()
{
	return false;
}

bool Sample::Release()
{
	return false;
}