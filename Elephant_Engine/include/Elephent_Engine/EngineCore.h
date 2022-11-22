#pragma once
#include "Window.h"
#include "Device.h"
#include "Input.h"
#include "Timer.h"
#include "Writer.h"

class EngineCore
{
private:
	bool is_running_ = true;
private:
	bool EngineInit();
	bool EngineFrame();
	bool EngineRender();
	bool EngineRelease();
public:
	virtual bool Init() { return true; };
	virtual bool Frame() { return true; };
	virtual bool Render() { return true; };
	virtual bool Release() { return true; };
public:
	bool Run();
};

