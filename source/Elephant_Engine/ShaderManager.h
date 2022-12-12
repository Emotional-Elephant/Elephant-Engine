#pragma once
#include"stdafx.h"

class ShaderManager : public Singleton<ShaderManager> {
	friend class Singleton<ShaderManager>;
private:
	std::unordered_map<std::wstring, std::pair<ComPtr<ID3DBlob>, ComPtr<ID3D11VertexShader>>>	vs_list_;
	std::unordered_map<std::wstring, ComPtr<ID3D11PixelShader>>									ps_list_;
public:
	ComPtr<ID3D11VertexShader>	GetVertexShader(std::wstring file_name, std::string func_name = "VS");
	ComPtr<ID3DBlob>			GetVSCode(std::wstring file_name, std::string func_name = "VS");
	ComPtr<ID3D11PixelShader>	GetPixelShader(std::wstring file_name, std::string func_name = "PS");
	bool	Release();
private:
	ShaderManager() {};
	~ShaderManager() { Release(); };
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager& operator=(const ShaderManager&) = delete;
};