#include "Device.h"

HRESULT Device::CreateDevice()
{
    UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL pFeatureLevel;
    D3D_FEATURE_LEVEL pFeatureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_0,
    };
    UINT FeatureLevels = 1;

    HRESULT hr = D3D11CreateDevice(
        nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL,
        createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION,
        d3d11_device_.GetAddressOf(),
        &pFeatureLevel,
        d3d11_device_context_.GetAddressOf()
    );

    return hr;
}

HRESULT Device::CreateDXGIDevice()
{
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)dxgi_factory_.GetAddressOf());
    return hr;
}

HRESULT Device::CreateSwapChain()
{
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = Window::GetInstance().GetRTClient().right;
    sd.BufferDesc.Height = Window::GetInstance().GetRTClient().bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = Window::GetInstance().GetHWindow();
    sd.Windowed = true;

    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    HRESULT hr = dxgi_factory_->CreateSwapChain(
        d3d11_device_.Get(), 
        &sd, 
        dxgi_swap_chain_.GetAddressOf()
    );
    return hr;
}

HRESULT Device::CreateRenderTargetView()
{
    ID3D11Texture2D* pBackBuffer = nullptr;
    dxgi_swap_chain_->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
    HRESULT hr = d3d11_device_->CreateRenderTargetView(pBackBuffer,
        NULL, d3d11_rtv_.GetAddressOf());
    pBackBuffer->Release();
    return hr;
}

void Device::CreateViewport()
{
    D3D11_VIEWPORT vp;
    vp.Width = Window::GetInstance().GetRTClient().right;
    vp.Height = Window::GetInstance().GetRTClient().bottom;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    d3d11_device_context_->RSSetViewports(1, &vp);
}

bool Device::Init()
{
    HRESULT hr;
    if (FAILED(hr = CreateDXGIDevice()))
    {
        return false;
    }
    if (FAILED(hr = CreateDevice()))
    {
        return false;
    }
    if (FAILED(hr = CreateSwapChain()))
    {
        return false;
    }
    if (FAILED(hr = CreateRenderTargetView()))
    {
        return false;
    }
    CreateViewport();
    return true;
}

bool Device::Frame()
{
	return true;
}

bool Device::Render()
{
    d3d11_device_context_->OMSetRenderTargets(1, d3d11_rtv_.GetAddressOf(), NULL);
    float color[4] = { 0.7f, 0.5f, 0.3f, 1.0f };
    d3d11_device_context_->ClearRenderTargetView(d3d11_rtv_.Get(), color);
    d3d11_device_context_->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    return true;
}

bool Device::Release()
{
	return true;
}
