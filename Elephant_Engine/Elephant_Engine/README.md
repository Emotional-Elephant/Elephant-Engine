# Elephant-Engine

# DirectX로 구성한 게임 엔진

- [엔진의 주요 요소](#엔진의-주요-요소)
  - [EngineCore](#EngineCore)
   	- [개요](#EngineCore-개요)
	- [특징](#EngineCore-특징)
	- [활용](#EngineCore-활용)
  - [Device](#Device)
	- [개요](#Device-개요)
	- [특징](#Device-특징)
	- [주요 함수](#Device-주요-함수)
      - [GetDevice()](#GetDevice)
      - [GetDeviceContext()](#GetDeviceContext)
      - [GetSwapChain()](#GetSwapChain)
  - [Window](#Window)
	- [개요](#Window-개요)
	- [특징](#Window-특징)
	- [주요 함수](#Window-주요-함수)
      - [GetHWindow()](#GetHWindow)
      - [GetRTWindow()](#GetRTWindow)
      - [GetRTClient()](#GetRTClient)
      - [SetWindow()](#SetWindow)
- [리소스 매니저](#리소스-매니저)
- [기타 툴](#기타-툴)
# 엔진의 주요 요소
## EngineCore
### EngineCore 개요
 엔진의 전체적인 동작을 관리하는 클래스입니다. 
### EngineCore 특징
 - [템플릿 메소드 패턴](https://ko.wikipedia.org/wiki/%ED%85%9C%ED%94%8C%EB%A6%BF_%EB%A9%94%EC%86%8C%EB%93%9C_%ED%8C%A8%ED%84%B4)을 활용하여 작성된 클래스입니다.
    - 가상함수로 구현되어 재정의 가능한 Init(), Frame(), Render(), Release() 함수가 정의되어 있습니다.
    - 따라서 EngineInit() 등 Engine~ 함수에는 엔진이 해야할 고정된 동작이 작성되어 있고, 앞서 언급한 재정의 가능한 함수를 적절한 위치에 호출하도록 하여
 재정의한 함수들이 적절한 위치에서 동작할 수 있도록 하였습니다.
### EngineCore-활용
 게임을 구성할 클래스가 EngineCore 클래스를 상속받고, 원하는 동작을 재정의 가능한 Init(), Frame(), Render(), Release() 함수를 통해 구현하면 됩니다.

## Device
### Device 개요
 렌더링 파이프라인을 구성하고 관리하기 위한 멤버들을 가지고 있는 클래스 입니다. 
Init() 함수를 통해 필요한 여러 객체를 초기화하여 유지하고, 필요할 때 반환해주는 역할을 합니다.
### Device 특징
- 싱글톤 클래스로 구현되어 있어 가지고 있는 멤버가 유일함을 보장합니다.
- 싱글톤 클래스로 구현되어 있어 전역적으로 접근이 가능합니다.
    - 다음과 같이 매크로로 구현되어 있으므로, 
```C++
#define I_Device Device::GetInstance()
```
    - 외부에서는 다음과 같이 활용하는 것이 가능합니다.
```C++
I_Device.GetDevice();
```
### Device 주요 함수
#### GetDevice
##### 개요
 [ID3D11Device](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11device)를 [ComPtr](https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170)형태로 반환해주는 함수입니다.
##### 매개변수
없음
##### 반환값
```C++
ComPtr<ID3D11Device>
```
##### 사용예시
다음의 예시와 같이 렌더링 파이프라인의 구성 요소 생성 시에 활용할 수 있습니다.
```C++
	hr = I_Device.GetDevice()->CreateInputLayout(
		ied,
		NumElements,
		pVSCode->GetBufferPointer(),
		pVSCode->GetBufferSize(),
		&vertex_layout_);
```
##### 주의 사항
- 클래스의 멤버 변수 등 오래 들고 있는 변수의 형태로 저장하는 것을 지양  
 ComPtr은 스마트 포인터와 유사하게 참조 카운팅 방식으로 동작하므로, 
불가피한 상황이 아니라면 항상 지역 변수로 받거나 받아놓지 않고 바로 활용하여 Device 객체가 유일한 권한을 갖도록 합시다. 
 혹시 변경할 일이 생겨 재설정 시 다른 곳에서 변수를 들고 있다면 재대로된 삭제가 이루어지지 않기 때문에 이러한 조치를 취하는 것입니다.

#### GetDeviceContext
##### 개요
 [ID3D11DeviceContext](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11devicecontext)를 [ComPtr](https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170)형태로 반환해주는 함수입니다.
##### 매개변수
없음
##### 반환값
```C++
ComPtr<ID3D11DeviceContext>
```
##### 사용예시
다음의 예시와 같이 렌더링 파이프라인의 여러 요소 설정 시에 사용할 수 있습니다.
```C++
I_Device.GetDeviceContext()->IASetInputLayout(vertex_layout_);
```
##### 주의 사항
- 클래스의 멤버 변수 등 오래 들고 있는 변수의 형태로 저장하는 것을 지양  
 ComPtr은 스마트 포인터와 유사하게 참조 카운팅 방식으로 동작하므로, 
불가피한 상황이 아니라면 항상 지역 변수로 받거나 받아놓지 않고 바로 활용하여 Device 객체가 유일한 권한을 갖도록 합시다. 
 혹시 변경할 일이 생겨 재설정 시 다른 곳에서 변수를 들고 있다면 재대로된 삭제가 이루어지지 않기 때문에 이러한 조치를 취하는 것입니다.

#### GetSwapChain
##### 개요
 [IDXGISwapChain](https://learn.microsoft.com/en-us/windows/win32/api/dxgi/nn-dxgi-idxgiswapchain)를 [ComPtr](https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170)형태로 반환해주는 함수입니다.
##### 매개변수
없음
##### 반환값
```C++
ComPtr<IDXGISwapChain>
```
##### 사용예시
다음의 예시와 같이 현재의 백 버퍼와 프론트 버퍼 교체 시에 활용됩니다.
```C++
I_Device.GetSwapChain()->Present(0, 0);
```
##### 주의 사항
- 클래스의 멤버 변수 등 오래 들고 있는 변수의 형태로 저장하는 것을 지양  
 ComPtr은 스마트 포인터와 유사하게 참조 카운팅 방식으로 동작하므로, 
불가피한 상황이 아니라면 항상 지역 변수로 받거나 받아놓지 않고 바로 활용하여 Device 객체가 유일한 권한을 갖도록 합시다. 
 혹시 변경할 일이 생겨 재설정 시 다른 곳에서 변수를 들고 있다면 재대로된 삭제가 이루어지지 않기 때문에 이러한 조치를 취하는 것입니다.

## Window
### Window 개요
 화면을 출력할 창을 생성하고, 관리하는 클래스입니다.
### Window 특징
- 싱글톤 클래스로 구현되어 있어 가지고 있는 멤버가 유일함을 보장합니다.
- 싱글톤 클래스로 구현되어 있어 전역적으로 접근이 가능합니다.
    - 다음과 같이 매크로로 구현되어 있으므로, 
```C++
#define I_Window Window::GetInstance()
```
    - 외부에서는 다음과 같이 활용하는 것이 가능합니다.
```C++
I_Window.GetRTClient();
```
### Window 주요 함수
#### GetHWindow
##### 개요
 띄워진 창에 대한 핸들을 반환해주는 함수입니다.
##### 매개변수
없음
##### 반환값
```C++
HWND
```
##### 사용예시
 다음과 같이 SwapChain을 생성할 시, Swapchain은 윈도우에 직접적으로 출력을 할 수 있어야 하므로 Window 핸들을 가지고 있어야 합니다.
따라서 GetHWindow() 함수를 활용하여 작성할 수 있습니다.
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
##### 주의 사항
#### GetRTWindow
##### 개요
 띄워진 창의 위치와 크기를 반환하는 함수입니다.
##### 매개변수
없음
##### 반환값
창 위치와 크기를 나타내기 위해 RECT 구조체를 활용하여 반환합니다.
[RECT](https://learn.microsoft.com/en-us/dotnet/api/system.windows.rect?view=windowsdesktop-7.0)
##### 사용예시
 띄워진 창의 위치와 크기가 필요한 곳에서 활용할 수 있습니다.
##### 주의 사항
 GetRTWindow가 반환하는 창 위치와 크기는 타이틀바 등 전체 띄워진 창에 때한 위치, 크기이므로, 
실제 출력될 화면의 위치와 크기를 활용하기 위해서는 [GetRTClient()](#GetRTClient) 함수를 활용해야 합니다.
#### GetRTClient
##### 개요
 실제 출력이 이루어질 창의 위치와 크기를 반환하는 함수입니다.
##### 매개변수
없음
##### 반환값
창 위치와 크기를 나타내기 위해 RECT 구조체를 활용하여 반환합니다.
[RECT](https://learn.microsoft.com/en-us/dotnet/api/system.windows.rect?view=windowsdesktop-7.0)
##### 사용예시
 실제 출력이 이루어질 창의 위치와 크기가 필요한 곳에서 활용할 수 있습니다.
##### 주의 사항
 GetRTClient가 반환하는 창 위치와 크기는 실제 출력될 화면의 위치와 크기이므로, 
타이틀바 등 전체 띄워진 창에 때한 위치, 크기를 활용하기 위해서는 [GetRTWindow()](#GetRTWindow) 함수를 활용해야 합니다.
#### SetWindow
##### 개요
 들어온 매개변수에 따라 창에대한 설정을 진행하고, 창을 생성하여 띄워주는 함수입니다.
##### 매개변수
```C++
HINSTANCE hinstance // 창 설정을 위해 필요한 객체입니다.
const WCHAR* title  // 창의 타이틀바에 뜰 제목을 설정할 문자열입니다.
UINT width = 1024   // 창의 너비 입니다.
UINT height = 768   // 창의 높이 입니다.
```
##### 반환값
```C++
bool
```
true: 창의 설정이 제대로 이루어지고 잘 띄워졌을 경우
false: 에러가 발생했을 경우
##### 사용예시
다음의 예시와 같이 창을 생성(혹은 창 크기를 변경)할 시 호출하여 활용할 수 있습니다.
```C++
I_Window.SetWindow(hInstance, WINDOW_NAME, WINDOW_SIZE_X, WINDOW_SIZE_Y);
```
##### 주의 사항