#include "EngineCore.h"

bool EngineCore::EngineInit()
{
    I_Window.Init();
    I_Device.Init();
    I_Writer.Init();
    IDXGISurface1* pBackBuffer;
    I_Device.GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface1),
        (void**)&pBackBuffer);
    I_Writer.Set(pBackBuffer);
    pBackBuffer->Release();
    I_Input.Init();
    I_Timer.Init();
    return Init();
}

bool EngineCore::EngineFrame()
{
    I_Window.Frame();
    I_Device.Frame();
    I_Writer.Frame();
    I_Input.Frame();
    I_Timer.Frame();
    return Frame();
}

bool EngineCore::EngineRender()
{
    I_Device.Render();
    Render();
    I_Input.Render();
    I_Timer.Render();
    I_Writer.Render();
    I_Device.GetSwapChain()->Present(0, 0);
    return true;
}

bool EngineCore::EngineRelease()
{
    Release();
    I_Timer.Release();
    I_Input.Release();
    I_Writer.Release();
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
