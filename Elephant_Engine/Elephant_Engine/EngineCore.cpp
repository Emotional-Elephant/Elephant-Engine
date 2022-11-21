#include "EngineCore.h"

bool EngineCore::EngineInit()
{
    I_Window.Init();
    I_Device.Init();
    return Init();
}

bool EngineCore::EngineFrame()
{
    return Frame();
}

bool EngineCore::EngineRender()
{
    I_Device.Render();
    Render();
    I_Device.GetSwapChain()->Present(0, 0);
    return true;
}

bool EngineCore::EngineRelease()
{
    Release();
    I_Device.Release();
    I_Window.Release();
    return true;
}

bool EngineCore::Run()
{
    EngineInit();
    while (is_running_) {
        if (I_Window.Run() == true) {
            EngineFrame();
            EngineRender();
        }
        else {
            is_running_ = false;
        }
    }
    EngineRelease();
    return true;
}
