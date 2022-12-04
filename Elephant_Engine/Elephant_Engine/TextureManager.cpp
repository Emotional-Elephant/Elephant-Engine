#include "TextureManager.h"

ComPtr<ID3D11ShaderResourceView> TextureManager::GetSRV(std::wstring file_name)
{
	ComPtr<ID3D11ShaderResourceView> texture_srv;
	auto iter = texture_list_.find(file_name);
	if (iter != texture_list_.end())
	{
		texture_srv = (iter->second)->texture_srv_;
		return texture_srv;
	}

	std::shared_ptr<Texture> texture = std::make_shared<Texture>();

	HRESULT hr = DirectX::CreateWICTextureFromFile(
		Device::GetInstance().GetDevice().Get(),
		Device::GetInstance().GetDeviceContext().Get(),
		file_name.c_str(),
		(ID3D11Resource**) texture->texture_.GetAddressOf(),
		texture->texture_srv_.GetAddressOf());
	if (FAILED(hr))
	{
		hr = DirectX::CreateDDSTextureFromFile(
			Device::GetInstance().GetDevice().Get(),
			Device::GetInstance().GetDeviceContext().Get(),
			file_name.c_str(),
			(ID3D11Resource**) texture->texture_.GetAddressOf(),
			texture->texture_srv_.GetAddressOf());
	}
	assert(hr);

	(texture->texture_)->GetDesc(&texture->texture_desc_);

	texture_srv = texture->texture_srv_;
	texture_list_.insert({ file_name, texture });

	return texture_srv;
}

bool TextureManager::Release()
{
    return false;
}
