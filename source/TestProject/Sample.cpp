#include "Sample.h"
#include "RenderManager.h"

#define WINDOW_SIZE_X 1024
#define WINDOW_SIZE_Y 768
#define WINDOW_NAME L"DirectXGameEngine"

int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPWSTR		lpCmdLine,
	int			nCmdShow) {

	Window::GetInstance().SetWindow(hInstance, WINDOW_NAME, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	Sample sample;
	sample.Run();

	return 0;
}

bool Sample::Init()
{
	debug_camera_ = std::make_shared<DebugCamera>();
	test_box_ = std::make_shared<TestBox>();

	test_box_->Init();
	debug_camera_->Init();
	return true;
}

bool Sample::Frame()
{
	test_box_->Frame();
	debug_camera_->Frame();
	return true;
}

bool Sample::Render()
{
	debug_camera_->Render();
	RenderManager::GetInstance().Render();
	return true;
}

bool Sample::Release()
{
	test_box_->Release();
	debug_camera_->Release();
	return true;
}