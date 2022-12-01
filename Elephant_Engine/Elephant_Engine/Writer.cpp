#include "Writer.h"
#include "Device.h"
#include "Input.h"

bool Writer::Init()
{
	HRESULT hr;
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, id2d1_factory_.GetAddressOf());
	if (FAILED(hr)) return false;
	hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)id_write_factory_.GetAddressOf());
	if (FAILED(hr)) return false;
	hr = id_write_factory_->CreateTextFormat(
		L"°íµñ",
		NULL,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		20,
		L"en-us",
		id_write_text_format_.GetAddressOf());
	if (FAILED(hr)) return false;
	cur_text_ = L"";

	return true;
}

bool Writer::Frame()
{
#ifdef _DEBUG
	cur_text_ = L"play time: " + std::to_wstring(Timer::GetInstance().GetTotalPlayTime()) + L"\n";
	cur_text_ += L"FPS: " + std::to_wstring(Timer::GetInstance().GetFPS()) + L"\n";
	cur_text_ += L"cur coord: ";
	cur_text_ += std::to_wstring(Input::GetInstance().GetMousePos().x) + L", ";
	cur_text_ += std::to_wstring(Input::GetInstance().GetMousePos().y);
#endif
	return true;
}

bool Writer::Render()
{
	Draw(0, 0, cur_text_, { 1,1,1,1 });
    return true;
}

bool Writer::Release()
{
    return true;
}

HRESULT Writer::CreateDXResource()
{
	Init();
	IDXGISurface1* pBackBuffer;
	Device::GetInstance().GetSwapChain()->GetBuffer(0, __uuidof(IDXGISurface1),
		(void**)&pBackBuffer);
	Set(pBackBuffer);
	pBackBuffer->Release();
	return S_OK;
}

HRESULT Writer::DeleteDXResource()
{
	id2d1_color_brush_ = nullptr;
	id2d1_render_target_ = nullptr;
	return S_OK;
}

bool Writer::Set(IDXGISurface1* dxgi_surface)
{
	D2D1_RENDER_TARGET_PROPERTIES props;
	ZeroMemory(&props, sizeof(props));
	props.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
	props.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	props.dpiX = 96;
	props.dpiY = 96;
	props.usage = D2D1_RENDER_TARGET_USAGE_NONE;
	props.minLevel = D2D1_FEATURE_LEVEL_DEFAULT;

	HRESULT hr = id2d1_factory_->CreateDxgiSurfaceRenderTarget(
		dxgi_surface,
		&props,
		&id2d1_render_target_);
	if (FAILED(hr)) return false;

	hr = id2d1_render_target_->CreateSolidColorBrush({ 0,0,0,1 },
		id2d1_color_brush_.GetAddressOf());
	if (FAILED(hr)) return false;

	return true;
}

bool Writer::Draw(float x, float y, std::wstring text, D2D1_COLOR_F color)
{
	id2d1_render_target_->BeginDraw();
	D2D1_RECT_F rt = { x, y, Window::GetInstance().GetRTClient().right, Window::GetInstance().GetRTClient().bottom };
	id2d1_color_brush_->SetColor(color);
	id2d1_color_brush_->SetOpacity(1.0f);
	id2d1_render_target_->DrawText(text.c_str(), text.size(), id_write_text_format_.Get(), rt, id2d1_color_brush_.Get());
	id2d1_render_target_->EndDraw();
	return true;
}
