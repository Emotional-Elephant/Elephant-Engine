#pragma once
#include"Timer.h"
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wrl.h>
using namespace Microsoft::WRL;

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

class Writer : public Singleton<Writer>
{
	friend class Singleton<Writer>;
private:
	ComPtr<ID2D1Factory>			id2d1_factory_;
	ComPtr<IDWriteFactory>			id_write_factory_;
	ComPtr<ID2D1RenderTarget>		id2d1_render_target_;
	ComPtr<IDWriteTextFormat>		id_write_text_format_;
	ComPtr<ID2D1SolidColorBrush>	id2d1_color_brush_;
	std::wstring					cur_text_;
public:
	virtual bool			Init();
	virtual bool			Frame();
	virtual bool			Render();
	virtual bool			Release();
public:
	virtual HRESULT			CreateDXResource();
	virtual HRESULT			DeleteDXResource();
public:
	bool					Set(IDXGISurface1* dxgi_surface);
	bool					Draw(float x, float y, std::wstring text, D2D1_COLOR_F color = { 0, 0, 0, 1 });
private:
	Writer() {};
	~Writer() = default;
	Writer(const Writer&) = delete;
	Writer& operator=(const Writer&) = delete;
};