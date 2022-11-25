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
	- [ShaderManager](#ShaderManager)
		- [개요](#ShaderManager-개요)
		- [특징](#ShaderManager-특징)
		- [주요 함수](#ShaderManager-주요-함수)
      	- [GetVertexShader()](#GetVertexShader)
      	- [GetVSCode()](#GetVSCode)
      	- [GetPixelShader()](#GetPixelShader)
- [기타 툴](#기타-툴)
  	- [Timer](#Timer)
		- [개요](#Timer-개요)
		- [특징](#Timer-특징)
		- [주요 함수](#Timer-주요-함수)
      			- [GetTotalPlayTime()](#GetTotalPlayTime)
      			- [GetFrameInterval()](#GetFrameInterval)
      			- [GetFPS()](#fps_)
  	- [Input](#Input)
		- [개요](#Input-개요)
		- [특징](#Input-특징)
		- [주요 함수](#Input-주요-함수)
      			- [GetKey()](#GetKey)
      			- [GetMousePos()](#GetMousePos)
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
불가피한 상황이 아니라면 항상 지역 변수로 받거나 받아놓지 않고 바로 활용하여 Device 객체가 유일한 권한을 갖도록 하는 것이 좋습니다.
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
불가피한 상황이 아니라면 항상 지역 변수로 받거나 받아놓지 않고 바로 활용하여 Device 객체가 유일한 권한을 갖도록 하는 것이 좋습니다.
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
불가피한 상황이 아니라면 항상 지역 변수로 받거나 받아놓지 않고 바로 활용하여 Device 객체가 유일한 권한을 갖도록 하는 것이 좋습니다.
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


# 리소스 매니저
## ShaderManager
### ShaderManager 개요
 렌더링 파이프라인에서 정점에 대한 연산을 진행하고, 픽셀값을 설정하는데 필요한 셰이더에 대한 컴파일을 진행하고 그 결과로 나온 객체를 유지하여 필요한 곳에 반환해주는 객체입니다.
### ShaderManager 특징
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
- [플라이 웨이트 패턴](https://ko.wikipedia.org/wiki/%ED%94%8C%EB%9D%BC%EC%9D%B4%EC%9B%A8%EC%9D%B4%ED%8A%B8_%ED%8C%A8%ED%84%B4)을 활용하여, 프로젝트에 하나의 셰이더 파일당 하나의 객체 씩만 유지하도록 하였습니다.
 이를 통해 얻을 수 있는 효과는 다음과 같습니다.
    - 같은 셰이더 파일에 대해 여러 객체가 생성되는 것을 방지하여 메모리를 절약합니다.
    - 같은 셰이더에 대해 여러번 컴파일이 이루어지는 것을 방지하여 실행 시간을 절약합니다.
### ShaderManager 주요 함수
#### GetVertexShader
##### 개요
 [ID3D11VertexShader](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11vertexshader)를 [ComPtr](https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170)형태로 반환해주는 함수입니다.
##### 매개변수
```C++
std::wstring file_name          // 셰이더 코드가 작성된 파일의 파일 명입니다.
std::string func_name = "VS"    // hlsl 코드 내에서 진입점이 될 함수의 이름입니다.
```
##### 반환값
```C++
ComPtr<ID3D11VertexShader>
```
 hlsl코드를 컴파일하여 이진코드를 생성하고, 생성된 이진 코드로 생성한 셰이더의 ComPtr을 반환합니다.
##### 사용예시
 아래의 예시와 같이 정점 GetVertexShader 함수를 이용하여 생성이 완료된 정점 셰이더를 받아와 렌더링 파이프라인에 정점 셰이더를 설정하는데 사용할 수 있습니다.
```C++
	ComPtr<ID3D11VertexShader> vertex_shader;
	vertex_shader = I_Shader.GetVertexShader(vs_name_, vs_func_name_);

	I_Device.GetDeviceContext()->VSSetShader(vertex_shader.Get(), NULL, 0);
```
##### 주의 사항
- 클래스의 멤버 변수 등 오래 들고 있는 변수의 형태로 저장하는 것을 지양  
 ComPtr은 스마트 포인터와 유사하게 참조 카운팅 방식으로 동작하므로, 
불가피한 상황이 아니라면 항상 지역 변수로 받거나 받아놓지 않고 바로 활용하여 Device 객체가 유일한 권한을 갖도록 하는 것이 좋습니다.
 혹시 변경할 일이 생겨 재설정 시 다른 곳에서 변수를 들고 있다면 재대로된 삭제가 이루어지지 않기 때문에 이러한 조치를 취하는 것입니다.
#### GetVSCode
##### 개요
 [ID3DBlob](https://learn.microsoft.com/ko-kr/previous-versions/windows/desktop/legacy/ff728743(v=vs.85))를 [ComPtr](https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170)형태로 반환해주는 함수입니다.
##### 매개변수
```C++
std::wstring file_name          // 셰이더 코드가 작성된 파일의 파일 명입니다.
std::string func_name = "VS"    // hlsl 코드 내에서 진입점이 될 함수의 이름입니다.
```
##### 반환값
```C++
ComPtr<ID3DBlob>
```
 hlsl코드를 컴파일하여 이진코드를 생성하고, 생성된 이진 코드의 ComPtr을 반환합니다.
##### 사용예시
 정점 셰이더의 이진 코드는 [ID3D11InputLayout](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11inputlayout)을 생성하기 위해 활용됩니다.
따라서 다음 예시와 가팅 활용할 수 있습니다.
```C++
	ComPtr<ID3DBlob> pVSCode = I_Shader.GetVSCode(vs_name_, vs_func_name_);

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,28,D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT NumElements = sizeof(ied) / sizeof(ied[0]);
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
불가피한 상황이 아니라면 항상 지역 변수로 받거나 받아놓지 않고 바로 활용하여 Device 객체가 유일한 권한을 갖도록 하는 것이 좋습니다.
 혹시 변경할 일이 생겨 재설정 시 다른 곳에서 변수를 들고 있다면 재대로된 삭제가 이루어지지 않기 때문에 이러한 조치를 취하는 것입니다.
#### GetPixelShader
##### 개요
 [ID3D11PixelShader](https://learn.microsoft.com/en-us/windows/win32/api/d3d11/nn-d3d11-id3d11pixelshader)를 [ComPtr](https://learn.microsoft.com/en-us/cpp/cppcx/wrl/comptr-class?view=msvc-170)형태로 반환해주는 함수입니다.
##### 매개변수
```C++
std::wstring file_name          // 셰이더 코드가 작성된 파일의 파일 명입니다.
std::string func_name = "PS"    // hlsl 코드 내에서 진입점이 될 함수의 이름입니다.
```
##### 반환값
```C++
ComPtr<ID3D11PixelShader>
```
 hlsl코드를 컴파일하여 이진코드를 생성하고, 생성된 이진 코드로 생성한 셰이더의 ComPtr을 반환합니다.
##### 사용예시
 아래의 예시와 같이 정점 GetPixelShader 함수를 이용하여 생성이 완료된 픽셀 셰이더를 받아와 렌더링 파이프라인에 픽셀 셰이더를 설정하는데 사용할 수 있습니다.
```C++
	ComPtr<ID3D11PixelShader> pixel_shader;
	pixel_shader = I_Shader.GetPixelShader(ps_name_, ps_func_name_);

	I_Device.GetDeviceContext()->PSSetShader(pixel_shader.Get(), NULL, 0);
```
##### 주의 사항
- 클래스의 멤버 변수 등 오래 들고 있는 변수의 형태로 저장하는 것을 지양  
 ComPtr은 스마트 포인터와 유사하게 참조 카운팅 방식으로 동작하므로, 
불가피한 상황이 아니라면 항상 지역 변수로 받거나 받아놓지 않고 바로 활용하여 Device 객체가 유일한 권한을 갖도록 하는 것이 좋습니다.
 혹시 변경할 일이 생겨 재설정 시 다른 곳에서 변수를 들고 있다면 재대로된 삭제가 이루어지지 않기 때문에 이러한 조치를 취하는 것입니다.

# 기타 툴
## Timer
### Timer 개요
 이전 프레임과 시간차, 총 플레이 시간 등 여러 시간에 대한 관리를 진행하는 클래스입니다.
### Timer 특징
- 싱글톤 클래스로 구현되어 있어 가지고 있는 멤버가 유일함을 보장합니다.
- 싱글톤 클래스로 구현되어 있어 전역적으로 접근이 가능합니다.
    - 다음과 같이 매크로로 구현되어 있으므로, 
```C++
#define I_Timer Device::GetInstance()
```
    - 외부에서는 다음과 같이 활용하는 것이 가능합니다.
```C++
I_Timer.GetTotalPlayTime();
```
### Timer 주요 함수
#### GetTotalPlayTime
##### 개요
 게임 실행 시부터 총 플레이 시간을 실수 형태로 반환해주는 함수입니다.
##### 매개변수
없음
##### 반환값
```C++
float
```
##### 사용예시
총 플레이 시간이 필요한 위치에서 출하면 됩니다.
##### 주의 사항
#### GetFrameInterval
##### 개요
 이전 프레임과 다음 프레임 사이의 시간차를 실수 형태로 반환해주는 함수입니다.
##### 매개변수
없음
##### 반환값
```C++
float
```
##### 사용예시
 아래의 예시와 같이 어떤 객체의 이동을 표현할 때는 이전 프레임과 차이가 속력에 적용되어야 합니다.
이 때, GetFrameInterval() 함수를 활용할 수 있습니다.
```C++
vPosMovement[2] += 30.0f * I_Timer.GetFrameInterval();
```
##### 주의 사항
#### GetFPS
##### 개요
 이전 1초 동안 몇 프레임을 출력했는지를 정수 형태로 반환해줄 함수입니다.
##### 매개변수
없음
##### 반환값
```C++
UINT
```
##### 사용예시
 1초에 몇 프레임이 출력되고 있는 지 정보가 필요한 위치에서 활용할 수 있습니다.
##### 주의 사항
## Input
### Input 개요
 마우스의 위치, 마우스 클릭, 키보드 입력 등 여러 입력을 처리하고 입력 상태를 다른 클래스에 알려주기 위한 클래스입니다.
### Input 특징
- 싱글톤 클래스로 구현되어 있어 가지고 있는 멤버가 유일함을 보장합니다.
- 싱글톤 클래스로 구현되어 있어 전역적으로 접근이 가능합니다.
    - 다음과 같이 매크로로 구현되어 있으므로, 
```C++
#define I_Input Device::GetInstance()
```
    - 외부에서는 다음과 같이 활용하는 것이 가능합니다.
```C++
I_Input.GetMousePos();
```
### Input 주요 함수
#### GetKey
##### 개요
 각 키가 눌려 있는지, 누르는 중인지, 떼는 중인지 등의 상태를 인식하고, 이러한 상태를 필요한 클래스에게 알려주기 위한 클래스입니다.
##### 매개변수
없음
##### 반환값
자료형은 아래와 같지만, 
```C++
DWORD
```
실제로 반환되는 값은 아래의 열거형 상수 중 하나가 반환됩니다.
```C++
enum KeyState
{
	KEY_FREE = 0,	// 눌리지 않은 상태
	KEY_UP,		// 눌렀다가 떼고 있는 상태
	KEY_PUSH,	// 누르는 상태
	KEY_HOLD,	// 누른 상태 유지
};
```
##### 사용예시
아래와 같이 특정 키의 눌림 상태를 활용하여 발생할 이벤트를 연결할 수 있습니다. 
```C++
	if (I_Input.GetKey('W') == KEY_HOLD)
	{
		vPosMovement[2] += 30.0f * I_Timer.GetFrameInterval();
	}
```
문자는 위의 예시와 같이 char형 리터럴로 문자를 넘겨주면 되나, space, esc 등의 키는 아래의 문서를 참고 바랍니다.
[Virtual-Key 코드](https://learn.microsoft.com/ko-kr/windows/win32/inputdev/virtual-key-codes)
##### 주의 사항
#### GetMousePos
##### 개요
 화면 좌표계 기준으로 현재 마우스의 좌표를 반환해주는 함수입니다.
##### 매개변수
 없음
##### 반환값
[POINT](https://learn.microsoft.com/ko-kr/dotnet/api/system.windows.point?view=windowsdesktop-7.0)
##### 사용예시
 마우스의 좌표가 필요할 때 호출하여 사용하면 됩니다.
##### 주의 사항
