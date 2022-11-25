#include "Sample.h"

#define WINDOW_SIZE_X 1024
#define WINDOW_SIZE_Y 768
#define WINDOW_NAME L"DirectXGameEngine"

int APIENTRY wWinMain(
	HINSTANCE	hInstance,
	HINSTANCE	hPrevInstance,
	LPWSTR		lpCmdLine,
	int			nCmdShow) {

	I_Window.SetWindow(hInstance, WINDOW_NAME, WINDOW_SIZE_X, WINDOW_SIZE_Y);
	Sample sample;
	sample.Run();

	return 0;
}

bool Sample::Init()
{
	vertex_list_.resize(4);
	vertex_list_[0].p[0] = -0.5f;
	vertex_list_[0].p[1] = 0.5f;
	vertex_list_[0].p[2] = 0.0f;
	vertex_list_[1].p[0] = 0.5f;
	vertex_list_[1].p[1] = 0.5f;
	vertex_list_[1].p[2] = 0.0f;
	vertex_list_[2].p[0] = -0.5f;
	vertex_list_[2].p[1] = -0.5f;
	vertex_list_[2].p[2] = 0.0f;
	vertex_list_[3].p[0] = 0.5f;
	vertex_list_[3].p[1] = -0.5f;
	vertex_list_[3].p[2] = 0.0f;

	vertex_list_[0].c[0] = 1.0f;
	vertex_list_[0].c[1] = 0.5f;
	vertex_list_[0].c[2] = 1.0f;
	vertex_list_[0].c[3] = 1.0f;	
	vertex_list_[1].c[0] = 0.0f;
	vertex_list_[1].c[1] = 1.0f;
	vertex_list_[1].c[2] = 1.0f;
	vertex_list_[1].c[3] = 1.0f;	
	vertex_list_[2].c[0] = 0.0f;
	vertex_list_[2].c[1] = 1.0f;
	vertex_list_[2].c[2] = 1.0f;
	vertex_list_[2].c[3] = 1.0f;
	vertex_list_[3].c[0] = 1.0f;
	vertex_list_[3].c[1] = 1.0f;
	vertex_list_[3].c[2] = 0.0f;
	vertex_list_[3].c[3] = 1.0f;

	vertex_list_[0].t[0] = 0.0f;
	vertex_list_[0].t[1] = 0.0f;
	vertex_list_[1].t[0] = 1.0f;
	vertex_list_[1].t[1] = 0.0f;
	vertex_list_[2].t[0] = 0.0f;
	vertex_list_[2].t[1] = 1.0f;
	vertex_list_[3].t[0] = 1.0f;
	vertex_list_[3].t[1] = 1.0f;

	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(SimpleVertex) * vertex_list_.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &vertex_list_.at(0);
	I_Device.GetDevice()->CreateBuffer(
		&bd,
		&sd,
		&vertex_buffer_);

	index_list_.resize(6);
	index_list_[0] = 0;
	index_list_[1] = 1;
	index_list_[2] = 2;
	index_list_[3] = 2;
	index_list_[4] = 1;
	index_list_[5] = 3;

	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(DWORD) * index_list_.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &index_list_.at(0);
	I_Device.GetDevice()->CreateBuffer(
		&bd,
		&sd,
		&index_buffer_);

	HRESULT hr;
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

	return true;
}

bool Sample::Frame()
{
	return false;
}

bool Sample::Render()
{
	HRESULT hr;
	ComPtr<ID3D11VertexShader> vertex_shader;
	vertex_shader = I_Shader.GetVertexShader(vs_name_, vs_func_name_);

	ComPtr<ID3D11PixelShader> pixel_shader;
	pixel_shader = I_Shader.GetPixelShader(ps_name_, ps_func_name_);

	I_Device.GetDeviceContext()->IASetInputLayout(vertex_layout_);
	I_Device.GetDeviceContext()->VSSetShader(vertex_shader.Get(), NULL, 0);
	I_Device.GetDeviceContext()->PSSetShader(pixel_shader.Get(), NULL, 0);
	UINT stride = sizeof(SimpleVertex);
	UINT offset = 0;
	I_Device.GetDeviceContext()->IASetVertexBuffers(0, 1,
		&vertex_buffer_, &stride, &offset);
	I_Device.GetDeviceContext()->IASetIndexBuffer(index_buffer_,
		DXGI_FORMAT_R32_UINT, 0);

	if (index_buffer_ == nullptr)
		I_Device.GetDeviceContext()->Draw(vertex_list_.size(), 0);
	else
		I_Device.GetDeviceContext()->DrawIndexed(index_list_.size(), 0, 0);

	return true;
}

bool Sample::Release()
{
	return false;
}