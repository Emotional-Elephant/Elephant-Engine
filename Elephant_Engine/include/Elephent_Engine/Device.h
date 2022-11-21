#pragma once
#include "Singleton.h"
#include "Window.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
using namespace Microsoft::WRL;

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")

class Device : public Singleton<Device>
{
	friend class Singleton<Device>;
private:
	ComPtr<ID3D11Device>			d3d11_device_ = nullptr;
	ComPtr<ID3D11DeviceContext>		d3d11_device_context_ = nullptr;
	ComPtr<ID3D11RenderTargetView>	d3d11_rtv_ = nullptr;
	ComPtr<IDXGIFactory>			dxgi_factory_ = nullptr;
	ComPtr<IDXGISwapChain>			dxgi_swap_chain_ = nullptr;
public:
	ComPtr<ID3D11Device>			GetDevice() { return d3d11_device_; };
	ComPtr<ID3D11DeviceContext>		GetDeviceContext() { return d3d11_device_context_; };
	ComPtr<ID3D11RenderTargetView>	GetRTV() { return d3d11_rtv_; };
	ComPtr<IDXGIFactory>			GetFactory() { return dxgi_factory_; };
	ComPtr<IDXGISwapChain>			GetSwapChain() { return dxgi_swap_chain_; };
public:
	HRESULT CreateDevice();
	HRESULT CreateDXGIDevice();
	HRESULT CreateSwapChain();
	HRESULT CreateRenderTargetView();
	void	CreateViewport();
public:
	virtual bool Init();
	virtual bool Frame();
	virtual bool Render();
	virtual bool Release();
private:
	Device() {};
	~Device() = default;
	Device(const Device&) = delete;
	Device& operator=(const Device&) = delete;
};
#define I_Device Device::GetInstance()
