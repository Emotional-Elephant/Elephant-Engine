#include "Device.h"

HRESULT Device::CreateDevice()
{
	// 1) ����̽� ����
	// Direct3D�� ����ϱ� ���ؼ��� �ݵ�� ����̽� �� ����̽����ؽ�Ʈ�� ����(ȹ��)�ؾ� �۾��� ��������
	// ID3D11Device(���ҽ��� ������ ���)
	// ID3D11DeviceContext(������ ���)
	// ����̽��� ����� �и������� ���� ��Ƽ ������ �������� ��������
	// ��Ƽ �����带 �̿��� �������� �ϱ� ���ؼ��� DeferredContext�� ����ؾ� ��
	//
	// ID3D11Device // �ַ� ���ҽ��� ������ ���õ� �۾�
	// ID3D11DeviceContext // ������ ���ҽ����� ����Ͽ� ������ ó�� �� ����
	// IDXGISwapChain // ���� ���� �� �ĸ� ���۵��� ���� �� ����
	// ID3D11RenderTargetView // ������ �ĸ���۵� �߿��� ������(���) �� �����۸� ����
	// DXGI_SWAP_CHAIN_DESC // ������ ����ü�� ��ü�� �Ӽ��� ����
	// D3D11_VIEWPORT //������ �ȿ��� ������ �� ������ ����
	// 
	// D3D_FEATURE_LEVEL Direct3D������ ������ �� Ư�� �����̶� ��
	// ���õ� ������ ���� �����ϴ� ���̴������� �ٸ��� �ȴ�. �츮�� ���̴� 5.0�� ������ ����� ���̱� ������ D3D_FEATURE_LEVEL_11_0���� ����
	// 
	// D3D_DRIVER_TYPE�� ����̽��� ���� Ÿ���� �����ϸ� D3D_DRIVER_TYPE������ ���� �� �ϳ��� ��� �ȴ�.
	// Direct11�� �ϵ���������� �����Ѵٸ� D3D_DRIVER_TYPE_HARDWARE���� �����ϰ� �׷��� ���� ��� 
	// D3D_DRIVER_TYPE_WARP �Ǵ� D3D_DRIVER_TYPE_REFFERENCE(GPU�� ������ CPU���� ����ó�� �Ѵٴ� ��)�� ���
	// 
	// ���� ���۸��� ������ �ø���
	// ������ۿ� ���� �������ϸ� ������ ������ ���� ������ ȭ�� �������� �߻�
	// ����ü���� �����ϴ� ������ �� ���� ���۸� ����� ����ϱ� ����
	// �����İ� ��ü ����� ���
	// 
	// 
	// 
	// **CreateDeviceAndSwapChain**
	// IDXGIAdapter* pAdapter // ���÷��� �ý����̸� �̰��� NULL�̸� �� ���÷��� ����� ��ġ�� ����
	// D3D_DRIVER_TYPE DriverType // ����̽� ����̽� ����̹��� Ÿ�� �߿� �ϳ��� �Ǿ�� ��
	// HMODULE Software // �Ϲ������� NULL
	// UINT Flags // ����̽� ���� �÷��׷ν� D3D11_CREATE_DEVICE_FLAG�� �ϳ��� ���ȴ�., ��Ʈ ������ ����
	// D3D_FEATURE_LEVEL* pFeatureLevels //enum D3D_FEATURE_LEVEL�� �ּ� �� �迭�� �ּ�
	// UINT FeatureLevels // pFeatureLevels �迭�� ����
	// UINT SDKVersion // SDK������ ��Ÿ���� �÷��׷� D3D11_SDK_VERSION�� ����ϸ� ��
	// DXGI_SWAP_CHAIN_DESC* pSwapChainDesc // ����ü�� �Ӽ� ����
	// IDXGISwapChain** ppSwapChain 
	// ID3D11Device** ppDevice, // 
	// D3D_FEATURE_LEVEL* pFeatureLevel,
	// ID3D11DeviceContext** ppImmediateContext
	//
	// 
	//


	HRESULT hr;
	UINT createDeviceFlags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;
#ifdef _DEBUG
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL pFeatureLevel;
	D3D_FEATURE_LEVEL pFeatureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT FeatureLevels = 1;
	hr = D3D11CreateDevice(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags, pFeatureLevels, 1, D3D11_SDK_VERSION, &_pd3dDevice, &pFeatureLevel, &_pImmediateContext);
	//pd3dDevice �ٸ� �������̽� ������ ���
	//pImmediateContext ������ �������̽��� ���(����, ����)�� ��
	return hr;
}

HRESULT Device::CreateDXGIDevice()
{
	// 2) ���丮 ����
	// ����ü�� ��ü�� �����ϱ� ���� ����
	// 
	// DXGI DirectX10�� ���Ӱ� ����
	// �������� Ŀ�θ�带 ������ �ִ� �ܰ�
	// Ŀ�� ��� ����̺� �� �ý��� �ϵ����� ����ϴ� ���� ����
	//
	/*HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&_pGIFactory);*/
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)_pGIFactory.GetAddressOf());
	return hr;
}

HRESULT Device::CreateSwapChain()
{
	// 3) ����ü�� ����
	// �ĸ�(��)���� ���� -> �������
	//
	// DXGI_SWAP_CHAIN_DESC
	//DXGI_MODE_DESC BufferDesc; ����� ��带 ��Ÿ���� DXGI_MODE_DESC ����
	//DXGI_SAMPLE_DESC SampleDesc; ��Ƽ ���ø� �Ű� ������ ��Ÿ���� ����
	//DXGI_USAGE BufferUsage; ����� ǥ�� ���� �� CPU �׼��� �ɼ��� ��Ÿ���� DXGI_USAGE ���� �� ���, ���̴��� �Է��ϰų� ���� Ÿ�� ������� ��� �� �� �ִ�.
	//UINT BufferCount; ���� ü���� ���� ����
	//HWND OutputWindow; ��� â�� HWND �ڵ�, NULL�� �� �� ����
	//BOOL Windowed; ������ ��� = TRUE, Ǯ��ũ�� ��� = FALSE
	//DXGI_SWAP_EFFECT SwapEffect; �ø��� ���� ���� Ÿ�� ������ ������ ó���ϱ� ���� DXGI_SWAP_EFFECT ���� �� ����� �ϳ��� �����ȴ�
	//UINT Flags; ����ü�ε��� �ɼ��� ��Ÿ���� DXGI_SWAP_CHAIN_FLAG ���� �� ����̴�.
	// 
	// DXGI_MODE_DESC
	//UINT Width; �ػ��� �ʺ� ��Ÿ���� ��
	//UINT Height; �ػ� ���̸� ��Ÿ���� ��
	//DXGI_RATIONAL RefreshRate; ����󵵸� ��Ÿ���� DXGI_RATIONAL ����
	//DXGI_FORMAT Format; ����� ����ȼ� ������ ��Ÿ���� DXGI_FORMAT ����
	//DXGI_MODE_SCANLINE_ORDER ScanlineOrdering; �ֻ缱 ������ ����� ������ Ÿ������
	//DXGI_MODE_SCALING Scaling; ũ�� ���� ��带 ��Ÿ����
	// 
	// DXGI_RATIONAL
	// UINT Numerator ������� ���ڰ�(���� 60 ���� ����Ѵ�)
	// UINT Denominator ������� �и�
	// 
	// DXGI_FORMAT
	// �� ������ �ȼ� ������ ����
	// �Ϲ������� 32��Ʈ �ȼ� ����(DXGI_FORMAT_R8G8B8A8_UNORM)�� ���� ���(����ǥ�� ������� ���̵� ���)
	// 
	// DXGI_SAMPLE_DESC
	// UINT Count; //�ȼ� ������ ��Ƽ ���ø��� ��
	// UINT Quality; // �̹����� ǰ�� ������ ��ȯ�ȴ�. ǰ���� �������� ������ ���� => 1�� �����Ǹ� ��Ƽ ���ø��� ���� �ʰڴٴ� �Ͱ� ����
	// 
	// DXGI_USAGE
	// ����ü���� ���۸� �����Ϸ��� �ݵ�� DXGI_USAGE_RENDER_TARGET_OUTPUT �̾�� ��
	// 
	// DXGI_SWAP_EFFECT
	// DXGI_SWAP_EFFECT_DISCARD Present�� ȣ���ϰ� �Ǹ� �� ������ ������ ����
	// DXGI_SWAP_EFFECT_SEQUENTIAL Present�� ȣ���ϰ� �Ǹ� �� ������ ������ �����ȴ�. �� �÷��״� ��Ƽ ���ø��� �Բ� ����� �� ����.
	// 
	// DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH �ػ󵵿� �°� ��üȭ��� �� ����
	//
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = _rtClient.right;
	sd.BufferDesc.Height = _rtClient.bottom;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; // �ѹ� Ȯ���غ���
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = _hWnd;
	sd.Windowed = true;

	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;

	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;

	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	return _pGIFactory->CreateSwapChain(_pd3dDevice.Get(), &sd, _pSwapChain.GetAddressOf());
}

HRESULT Device::CreateRenderTargetView()
{
	// 4) ����Ÿ�ٺ� ����
	// 
	// ID3D11RenderTargetView �Լ��� ������ �� �� ������ �޷θ��ν� ����ü���� �� ���۸� ��Ÿ���� �������̽��̸� ������ ����ü�� ���ۿ� �����ϰ� �ȴ�.
	// ���� �׸� ������
	// 
	// GetBuffer
	// UINT Buffer //����ü�� �� ������ �ε���
	// REFIID riid //����ü�� �� ������ ��ȯ�Ǵ� �������̽� Ÿ���� ����
	// void** ppSurface // ������ Ÿ������ ������ ��ü�� �ּҰ� ��ȯ
	// 
	// �̷��� ��ȯ�� �� ���۴� ������ ����� ����� ������� �����ϱ� ���ؼ� CreateRenderTargetView �Լ��� ����
	// 
	// OMSetRenderTarget ������ ����Ÿ�ٺ並 ����̽��� ����� �� �ֵ��� ����(��� ���ձ�)
	// 
	// ����ü���� �� �� ���۵��� ���� D3D11Texture2D��ü�� ǥ��
	HRESULT hr;
	ID3D11Texture2D* pBackBuffer = nullptr;
	hr = _pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = _pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL, _pRTV.GetAddressOf());
	pBackBuffer->Release();
	if (FAILED(hr)) return hr;
	//_pImmediateContext->OMSetRenderTargets(1, &_pRTV, NULL);
	return S_OK;
}

void Device::CreateViewport()
{
	// 5)����Ʈ ����
	// 
	// ��ũ���� � ��ġ�� �۾��� ������ ǥ���� ������ ���� �����ϴ� ��
	//
	_vp.Width = _rtClient.right;
	_vp.Height = _rtClient.bottom;
	_vp.TopLeftX = 0;
	_vp.TopLeftY = 0;
	_vp.MinDepth = 0.0f;
	_vp.MaxDepth = 1.0f;
	_pImmediateContext->RSSetViewports(1, &_vp);
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
	return true;
}

bool Device::Release()
{
	/*if (_pd3dDevice) _pd3dDevice->Release();
	if (_pImmediateContext) _pImmediateContext->Release();
	if (_pGIFactory) _pGIFactory->Release();
	if (_pSwapChain) _pSwapChain->Release();
	if (_pRTV) _pRTV->Release();*/
	return true;
}
