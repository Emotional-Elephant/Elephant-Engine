#include "EngineCore.h"

bool EngineCore::EngineInit()
{
    I_Window.Init();
    Device::GetInstance().Init();
    Writer::GetInstance().Init();
    IDXGISurface1* pBackBuffer;
    Device::GetInstance().GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface1),
        (void**)&pBackBuffer);
    Writer::GetInstance().Set(pBackBuffer);
    pBackBuffer->Release();
    Input::GetInstance().Init();
    Timer::GetInstance().Init();
    return Init();
}

bool EngineCore::EngineFrame()
{
    I_Window.Frame();
    Device::GetInstance().Frame();
    Writer::GetInstance().Frame();
    Input::GetInstance().Frame();
    Timer::GetInstance().Frame();
    return Frame();
}

bool EngineCore::EngineRender()
{
    Device::GetInstance().Render();
    Render();
    Input::GetInstance().Render();
    Timer::GetInstance().Render();
    Writer::GetInstance().Render();
    Device::GetInstance().GetSwapChain()->Present(0, 0);
    return true;
}

bool EngineCore::EngineRelease()
{
    Release();
    Timer::GetInstance().Release();
    Input::GetInstance().Release();
    Writer::GetInstance().Release();
    Device::GetInstance().Release();
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
