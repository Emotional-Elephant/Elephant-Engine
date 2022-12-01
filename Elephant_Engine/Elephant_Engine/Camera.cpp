#include "Camera.h"

HRESULT Camera::CreateConstantBuffer()
{
    HRESULT hr;
    D3D11_BUFFER_DESC       bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.ByteWidth = sizeof(VS_CONSTANT_BUFFER_CAMERA) * 1;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA  sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.pSysMem = &constant_buffer_data_;
    hr = Device::GetInstance().GetDevice()->CreateBuffer(
        &bd,
        &sd,
        constant_buffer_.GetAddressOf());
    return hr;
}

bool Camera::Init()
{
    SetValues();
	HRESULT hr = CreateConstantBuffer();
	assert(FAILED(hr));
	return true;
}

bool Camera::Render()
{
    constant_buffer_data_.view_matrix_ = TMatrix::CreateLookAt(m_vPosition, m_vTarget, m_vUp);
    constant_buffer_data_.view_matrix_.Transpose();
    constant_buffer_data_.proj_matrix_ = TMatrix::CreatePerspectiveFieldOfView(m_fovy, m_Aspect, m_fNearPlane, m_fFarPlane);
    constant_buffer_data_.proj_matrix_.Transpose();
    Device::GetInstance().GetDeviceContext()->UpdateSubresource(
        constant_buffer_.Get(), 0, nullptr,
        &constant_buffer_data_, 0, 0);
    Device::GetInstance().GetDeviceContext()->VSSetConstantBuffers(1, 1, constant_buffer_.GetAddressOf());
	return true;
}

bool Camera::Release()
{
	return true;
}
