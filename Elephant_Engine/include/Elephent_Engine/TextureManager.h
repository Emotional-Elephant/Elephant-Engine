#pragma once
#include "stdafx.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#pragma comment(lib, "../lib/DirectXTK.lib")

struct Texture {
	ComPtr<ID3D11Texture2D>				texture_;
	ComPtr<ID3D11ShaderResourceView>	texture_srv_;
	D3D11_TEXTURE2D_DESC				texture_desc_;
};

class TextureManager: public Singleton<TextureManager>
{
	friend class Singleton<TextureManager>;
private:
	std::unordered_map<std::wstring, std::shared_ptr<Texture>> texture_list_;
public:
	ComPtr<ID3D11ShaderResourceView>	GetSRV(std::wstring file_name);
	bool								Release();
private:
	TextureManager() {};
	~TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
};

#define I_Tex TextureManager::GetInstance()