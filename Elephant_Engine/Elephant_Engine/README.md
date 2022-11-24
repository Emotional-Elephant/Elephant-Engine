# Elephant-Engine

# DirectX�� ������ ���� ����

- [������ �ֿ� ���](#������-�ֿ�-���)
  - [EngineCore](#EngineCore)
   	- [����](#EngineCore-����)
	- [Ư¡](#EngineCore-Ư¡)
	- [Ȱ��](#EngineCore-Ȱ��)
  - [Device](#Device)
	- [����](#Device-����)
	- [Ư¡](#Device-Ư¡)
	- [�ֿ� �Լ�](#Device-�ֿ�-�Լ�)
      - [GetDevice()](#GetDevice)
      - [GetDeviceContext()](#GetDeviceContext)
      - [GetSwapChain()](#GetSwapChain)
  - [Window](#Window)
	- [����](#Window-����)
	- [Ư¡](#Window-Ư¡)
	- [�ֿ� �Լ�](#Window-�ֿ�-�Լ�)
      - [GetHWindow()](#GetHWindow)
      - [GetRTWindow()](#GetRTWindow)
      - [GetRTClient()](#GetRTClient)
      - [SetWindow()](#SetWindow)
- [���ҽ� �Ŵ���](#���ҽ�-�Ŵ���)
- [��Ÿ ��](#��Ÿ-��)
# ������ �ֿ� ���
## EngineCore
### EngineCore ����
 ������ ��ü���� ������ �����ϴ� Ŭ�����Դϴ�. 
### EngineCore Ư¡
 - [���ø� �޼ҵ� ����](https://ko.wikipedia.org/wiki/%ED%85%9C%ED%94%8C%EB%A6%BF_%EB%A9%94%EC%86%8C%EB%93%9C_%ED%8C%A8%ED%84%B4)�� Ȱ���Ͽ� �ۼ��� Ŭ�����Դϴ�.
    - �����Լ��� �����Ǿ� ������ ������ Init(), Frame(), Render(), Release() �Լ��� ���ǵǾ� �ֽ��ϴ�.
    - ���� EngineInit() �� Engine~ �Լ����� ������ �ؾ��� ������ ������ �ۼ��Ǿ� �ְ�, �ռ� ����� ������ ������ �Լ��� ������ ��ġ�� ȣ���ϵ��� �Ͽ�
 �������� �Լ����� ������ ��ġ���� ������ �� �ֵ��� �Ͽ����ϴ�.
### EngineCore-Ȱ��
 ������ ������ Ŭ������ EngineCore Ŭ������ ��ӹް�, ���ϴ� ������ ������ ������ Init(), Frame(), Render(), Release() �Լ��� ���� �����ϸ� �˴ϴ�.

## Device
### Device ����
 ������ ������������ �����ϰ� �����ϱ� ���� ������� ������ �ִ� Ŭ���� �Դϴ�. 
Init() �Լ��� ���� �ʿ��� ���� ��ü�� �ʱ�ȭ�Ͽ� �����ϰ�, �ʿ��� �� ��ȯ���ִ� ������ �մϴ�.
### Device Ư¡
- �̱��� Ŭ������ �����Ǿ� �־� ������ �ִ� ����� �������� �����մϴ�.
- �̱��� Ŭ������ �����Ǿ� �־� ���������� ������ �����մϴ�.
    - ������ ���� ��ũ�η� �����Ǿ� �����Ƿ�, 
```C++
#define I_Device Device::GetInstance()
```
    - �ܺο����� ������ ���� Ȱ���ϴ� ���� �����մϴ�.
```C++
I_Device.GetDevice();
```
### Device �ֿ� �Լ�
#### GetDevice
##### ����
 [ID3D11Device](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11device)�� [ComPtr](https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170)���·� ��ȯ���ִ� �Լ��Դϴ�.
##### �Ű�����
����
##### ��ȯ��
```C++
ComPtr<ID3D11Device>
```
##### ��뿹��
������ ���ÿ� ���� ������ ������������ ���� ��� ���� �ÿ� Ȱ���� �� �ֽ��ϴ�.
```C++
	hr = I_Device.GetDevice()->CreateInputLayout(
		ied,
		NumElements,
		pVSCode->GetBufferPointer(),
		pVSCode->GetBufferSize(),
		&vertex_layout_);
```
##### ���� ����
- Ŭ������ ��� ���� �� ���� ��� �ִ� ������ ���·� �����ϴ� ���� ����  
 ComPtr�� ����Ʈ �����Ϳ� �����ϰ� ���� ī���� ������� �����ϹǷ�, 
�Ұ����� ��Ȳ�� �ƴ϶�� �׻� ���� ������ �ްų� �޾Ƴ��� �ʰ� �ٷ� Ȱ���Ͽ� Device ��ü�� ������ ������ ������ �սô�. 
 Ȥ�� ������ ���� ���� �缳�� �� �ٸ� ������ ������ ��� �ִٸ� ���ε� ������ �̷������ �ʱ� ������ �̷��� ��ġ�� ���ϴ� ���Դϴ�.

#### GetDeviceContext
##### ����
 [ID3D11DeviceContext](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11devicecontext)�� [ComPtr](https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170)���·� ��ȯ���ִ� �Լ��Դϴ�.
##### �Ű�����
����
##### ��ȯ��
```C++
ComPtr<ID3D11DeviceContext>
```
##### ��뿹��
������ ���ÿ� ���� ������ ������������ ���� ��� ���� �ÿ� ����� �� �ֽ��ϴ�.
```C++
I_Device.GetDeviceContext()->IASetInputLayout(vertex_layout_);
```
##### ���� ����
- Ŭ������ ��� ���� �� ���� ��� �ִ� ������ ���·� �����ϴ� ���� ����  
 ComPtr�� ����Ʈ �����Ϳ� �����ϰ� ���� ī���� ������� �����ϹǷ�, 
�Ұ����� ��Ȳ�� �ƴ϶�� �׻� ���� ������ �ްų� �޾Ƴ��� �ʰ� �ٷ� Ȱ���Ͽ� Device ��ü�� ������ ������ ������ �սô�. 
 Ȥ�� ������ ���� ���� �缳�� �� �ٸ� ������ ������ ��� �ִٸ� ���ε� ������ �̷������ �ʱ� ������ �̷��� ��ġ�� ���ϴ� ���Դϴ�.

#### GetSwapChain
##### ����
 [IDXGISwapChain](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiswapchain)�� [ComPtr](https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170)���·� ��ȯ���ִ� �Լ��Դϴ�.
##### �Ű�����
����
##### ��ȯ��
```C++
ComPtr<IDXGISwapChain>
```
##### ��뿹��
������ ���ÿ� ���� ������ �� ���ۿ� ����Ʈ ���� ��ü �ÿ� Ȱ��˴ϴ�.
```C++
I_Device.GetSwapChain()->Present(0, 0);
```
##### ���� ����
- Ŭ������ ��� ���� �� ���� ��� �ִ� ������ ���·� �����ϴ� ���� ����  
 ComPtr�� ����Ʈ �����Ϳ� �����ϰ� ���� ī���� ������� �����ϹǷ�, 
�Ұ����� ��Ȳ�� �ƴ϶�� �׻� ���� ������ �ްų� �޾Ƴ��� �ʰ� �ٷ� Ȱ���Ͽ� Device ��ü�� ������ ������ ������ �սô�. 
 Ȥ�� ������ ���� ���� �缳�� �� �ٸ� ������ ������ ��� �ִٸ� ���ε� ������ �̷������ �ʱ� ������ �̷��� ��ġ�� ���ϴ� ���Դϴ�.

## Window
### Window ����
 ȭ���� ����� â�� �����ϰ�, �����ϴ� Ŭ�����Դϴ�.
### Window Ư¡
- �̱��� Ŭ������ �����Ǿ� �־� ������ �ִ� ����� �������� �����մϴ�.
- �̱��� Ŭ������ �����Ǿ� �־� ���������� ������ �����մϴ�.
    - ������ ���� ��ũ�η� �����Ǿ� �����Ƿ�, 
```C++
#define I_Window Window::GetInstance()
```
    - �ܺο����� ������ ���� Ȱ���ϴ� ���� �����մϴ�.
```C++
I_Window.GetRTClient();
```
### Window �ֿ� �Լ�
#### GetHWindow
##### ����
 ����� â�� ���� �ڵ��� ��ȯ���ִ� �Լ��Դϴ�.
##### �Ű�����
����
##### ��ȯ��
```C++
HWND
```
##### ��뿹��
 ������ ���� SwapChain�� ������ ��, Swapchain�� �����쿡 ���������� ����� �� �� �־�� �ϹǷ� Window �ڵ��� ������ �־�� �մϴ�.
���� GetHWindow() �Լ��� Ȱ���Ͽ� �ۼ��� �� �ֽ��ϴ�.
```C++
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Width = I_Window.GetRTClient().right;
    sd.BufferDesc.Height = I_Window.GetRTClient().bottom;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
/****************************************************************/
    sd.OutputWindow = I_Window.GetHWindow();
/****************************************************************/
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
```
##### ���� ����
#### GetRTWindow
##### ����
 ����� â�� ��ġ�� ũ�⸦ ��ȯ�ϴ� �Լ��Դϴ�.
##### �Ű�����
����
##### ��ȯ��
â ��ġ�� ũ�⸦ ��Ÿ���� ���� RECT ����ü�� Ȱ���Ͽ� ��ȯ�մϴ�.
[RECT](https://learn.microsoft.com/en-us/dotnet/api/system.windows.rect?view=windowsdesktop-7.0)
##### ��뿹��
 ����� â�� ��ġ�� ũ�Ⱑ �ʿ��� ������ Ȱ���� �� �ֽ��ϴ�.
##### ���� ����
 GetRTWindow�� ��ȯ�ϴ� â ��ġ�� ũ��� Ÿ��Ʋ�� �� ��ü ����� â�� ���� ��ġ, ũ���̹Ƿ�, 
���� ��µ� ȭ���� ��ġ�� ũ�⸦ Ȱ���ϱ� ���ؼ��� [GetRTClient()](#GetRTClient) �Լ��� Ȱ���ؾ� �մϴ�.
#### GetRTClient
##### ����
 ���� ����� �̷���� â�� ��ġ�� ũ�⸦ ��ȯ�ϴ� �Լ��Դϴ�.
##### �Ű�����
����
##### ��ȯ��
â ��ġ�� ũ�⸦ ��Ÿ���� ���� RECT ����ü�� Ȱ���Ͽ� ��ȯ�մϴ�.
[RECT](https://learn.microsoft.com/en-us/dotnet/api/system.windows.rect?view=windowsdesktop-7.0)
##### ��뿹��
 ���� ����� �̷���� â�� ��ġ�� ũ�Ⱑ �ʿ��� ������ Ȱ���� �� �ֽ��ϴ�.
##### ���� ����
 GetRTClient�� ��ȯ�ϴ� â ��ġ�� ũ��� ���� ��µ� ȭ���� ��ġ�� ũ���̹Ƿ�, 
Ÿ��Ʋ�� �� ��ü ����� â�� ���� ��ġ, ũ�⸦ Ȱ���ϱ� ���ؼ��� [GetRTWindow()](#GetRTWindow) �Լ��� Ȱ���ؾ� �մϴ�.
#### SetWindow
##### ����
 ���� �Ű������� ���� â������ ������ �����ϰ�, â�� �����Ͽ� ����ִ� �Լ��Դϴ�.
##### �Ű�����
```C++
HINSTANCE hinstance // â ������ ���� �ʿ��� ��ü�Դϴ�.
const WCHAR* title  // â�� Ÿ��Ʋ�ٿ� �� ������ ������ ���ڿ��Դϴ�.
UINT width = 1024   // â�� �ʺ� �Դϴ�.
UINT height = 768   // â�� ���� �Դϴ�.
```
##### ��ȯ��
```C++
bool
```
true: â�� ������ ����� �̷������ �� ������� ���
false: ������ �߻����� ���
##### ��뿹��
������ ���ÿ� ���� â�� ����(Ȥ�� â ũ�⸦ ����)�� �� ȣ���Ͽ� Ȱ���� �� �ֽ��ϴ�.
```C++
I_Window.SetWindow(hInstance, WINDOW_NAME, WINDOW_SIZE_X, WINDOW_SIZE_Y);
```
##### ���� ����