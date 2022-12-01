#include "Renderable.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "RenderManager.h"

Renderable::Renderable()
{
	RegisterComponent();
	Init();
}

void Renderable::RegisterComponent()
{
	RenderManager::GetInstance().render_list_.push_back(std::make_shared<Renderable>(*this));
}

HRESULT Renderable::CreateVertexBuffer()
{
	SetVertexData();
	if (vertex_list_.empty()) return S_OK;
	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(Vertex) * vertex_list_.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &vertex_list_.at(0);
	HRESULT hr = Device::GetInstance().GetDevice()->CreateBuffer(
		&bd,
		&sd,
		vertex_buffer_.GetAddressOf());
	assert(SUCCEEDED(hr));

	return hr;
}

HRESULT Renderable::CreateIndexBuffer()
{
	SetIndexData();
	if (index_list_.empty()) return S_OK;
	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(DWORD) * index_list_.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;

	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &index_list_.at(0);
	HRESULT hr = Device::GetInstance().GetDevice()->CreateBuffer(
		&bd,
		&sd,
		index_buffer_.GetAddressOf());
	assert(SUCCEEDED(hr));

	return hr;
}

HRESULT Renderable::CreateConstantBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC       bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.ByteWidth = sizeof(VS_CONSTANT_BUFFER_RENDER) * 1;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	D3D11_SUBRESOURCE_DATA  sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = &constant_buffer_data_;
	hr = Device::GetInstance().GetDevice()->CreateBuffer(
		&bd,
		&sd,
		&constant_buffer_);
	assert(SUCCEEDED(hr));

	return hr;
}

HRESULT Renderable::CreateVertexLayout()
{
	HRESULT hr;
	ComPtr<ID3DBlob> pVSCode = ShaderManager::GetInstance().GetVSCode(vertex_shader_name_, vertex_function_name_);
	if (pVSCode.Get() == nullptr) return E_FAIL;

	D3D11_INPUT_ELEMENT_DESC ied[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,0,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,12,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0,24,D3D11_INPUT_PER_VERTEX_DATA, 0},
		{ "TEXTURE", 0, DXGI_FORMAT_R32G32_FLOAT, 0,40,D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT num_elements = sizeof(ied) / sizeof(ied[0]);
	hr = Device::GetInstance().GetDevice()->CreateInputLayout(
		ied,
		num_elements,
		pVSCode->GetBufferPointer(),
		pVSCode->GetBufferSize(),
		vertex_layout_.GetAddressOf());
	assert(SUCCEEDED(hr));

	return hr;
}

void Renderable::UpdateConstantBuffer()
{
	TMatrix scale_matrix;
	scale_matrix = scale_matrix.CreateScale(scale_);
	TQuaternion rotation_quaternion;
	D3DXQuaternionRotationYawPitchRoll(&rotation_quaternion, yaw_, pitch_, roll_);
	TMatrix rotation_matrix;
	D3DXMatrixRotationQuaternion(&rotation_matrix, &rotation_quaternion);
	TMatrix translation_matrix;
	translation_matrix = translation_matrix.CreateTranslation(location_);
	constant_buffer_data_.world_matrix_ = scale_matrix * rotation_matrix * translation_matrix;
	constant_buffer_data_.world_matrix_.Transpose();

	Device::GetInstance().GetDeviceContext()->UpdateSubresource(
		constant_buffer_.Get(), 0, nullptr,
		&constant_buffer_data_, 0, 0);
}

bool Renderable::Init()
{
	if (FAILED(CreateVertexBuffer())) {
		return false;
	}
	if (FAILED(CreateIndexBuffer())) {
		return false;
	}
	if (FAILED(CreateVertexLayout())) {
		return false;
	}
	if (FAILED(CreateConstantBuffer()))
	{
		return false;
	}
	return true;
}

bool Renderable::Frame()
{
    return true;
}

bool Renderable::Release()
{
    return true;
}

bool Renderable::Render()
{
	ComPtr<ID3D11ShaderResourceView> pSRV = nullptr;
	if (texture_name_ != L"") {
		pSRV = I_Tex.GetSRV(texture_name_);
	}

	ComPtr<ID3D11VertexShader> pVS = nullptr;
	pVS = ShaderManager::GetInstance().GetVertexShader(vertex_shader_name_, vertex_function_name_);
	if (pVS.Get() == nullptr) return false;

	ComPtr<ID3D11PixelShader> pPS = nullptr;
	pPS = ShaderManager::GetInstance().GetPixelShader(pixel_shader_name_, pixel_function_name);
	if (pPS.Get() == nullptr) return false;

	Device::GetInstance().GetDeviceContext()->PSSetShaderResources(0, 1, &pSRV);
	Device::GetInstance().GetDeviceContext()->IASetInputLayout(vertex_layout_.Get());
	Device::GetInstance().GetDeviceContext()->VSSetShader(pVS.Get(), NULL, 0);
	Device::GetInstance().GetDeviceContext()->PSSetShader(pPS.Get(), NULL, 0);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Device::GetInstance().GetDeviceContext()->IASetVertexBuffers(0, 1,
		&vertex_buffer_, &stride, &offset);
	Device::GetInstance().GetDeviceContext()->IASetIndexBuffer(index_buffer_.Get(),
		DXGI_FORMAT_R32_UINT, 0);

	UpdateConstantBuffer();
	Device::GetInstance().GetDeviceContext()->VSSetConstantBuffers(0, 1, constant_buffer_.GetAddressOf());

	if (index_buffer_ == nullptr)
		Device::GetInstance().GetDeviceContext()->Draw(vertex_list_.size(), 0);
	else
		Device::GetInstance().GetDeviceContext()->DrawIndexed(index_list_.size(), 0, 0);
	return true;
}