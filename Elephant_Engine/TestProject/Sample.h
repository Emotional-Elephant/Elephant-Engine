#pragma once
#include "stdafx.h"
#include "EngineCore.h"
#include "ShaderManager.h"

struct SimpleVertex
{
	float p[3];
	float c[4];
	float t[2];
public:
	SimpleVertex() {};
};


class Sample : public EngineCore
{
	std::vector<SimpleVertex>   vertex_list_;
	std::vector<int>			index_list_;
	ID3D11Buffer*				vertex_buffer_;
	ID3D11Buffer*				index_buffer_;
	ID3D11InputLayout*			vertex_layout_;
	std::wstring				vs_name_ = L"../data/shader/DefaultVertexShader.hlsl";
	std::wstring				ps_name_ = L"../data/shader/DefaultPixelShader.hlsl";
	std::string					vs_func_name_ = "VS";
	std::string					ps_func_name_ = "PS";
public:
	virtual bool Init() override;
	virtual bool Frame() override;
	virtual bool Render() override;
	virtual bool Release() override;
};
