#pragma once
#include"stdafx.h"

class ShaderManager : public Singleton<ShaderManager> {
	friend class Singleton<ShaderManager>;
private:
	std::unordered_map<std::wstring, std::pair<std::shared_ptr<ID3DBlob*>, std::shared_ptr<ID3D11VertexShader*>>>	vs_list_;
	std::unordered_map<std::wstring, std::shared_ptr<ID3D11PixelShader*>>										ps_list_;
public:
	HRESULT	GetVertexShader(std::weak_ptr<ID3D11VertexShader*>& vertex_shader, std::wstring file_name, std::string func_name = "VS");
	HRESULT	GetVSCode(std::weak_ptr<ID3DBlob*>& vs_code, std::wstring file_name, std::string func_name = "VS");
	HRESULT	GetPixelShader(std::weak_ptr<ID3D11PixelShader*>& pixel_shader, std::wstring file_name, std::string func_name = "PS");
	bool	Release();
private:
	ShaderManager() {};
	~ShaderManager() { Release(); };
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
};

#define I_Shader ShaderManager::GetInstance()