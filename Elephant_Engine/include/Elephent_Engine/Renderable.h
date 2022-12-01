#pragma once
#include "stdafx.h"

struct Vertex
{
	TVector3 p;
	TVector3 n;
	TVector4 c;
	TVector2 t;
public:
	Vertex() {};
	Vertex(TVector3 p, TVector4 c, TVector2 t) {
		this->p = p;
		this->c = c;
		this->t = t;
	};
	Vertex(TVector3 p, TVector3 n, TVector4 c, TVector2 t) {
		this->p = p;
		this->n = n;
		this->c = c;
		this->t = t;
	};
};

struct VS_CONSTANT_BUFFER_RENDER
{
	TMatrix		world_matrix_;
	TVector4	light_vector_;
};

class Renderable
{
protected:
	std::wstring				vertex_shader_name_ = L"";
	std::wstring				pixel_shader_name_ = L"";
	std::string					vertex_function_name_ = "";
	std::string					pixel_function_name = "";
	std::wstring				texture_name_ = L"";
	std::vector<Vertex>			vertex_list_;
	std::vector<DWORD>			index_list_;
protected:
	TVector3					scale_;
	TVector3					location_;
	float						yaw_;
	float						pitch_;
	float						roll_;
private:
	VS_CONSTANT_BUFFER_RENDER	constant_buffer_data_;
	ComPtr<ID3D11Buffer>		constant_buffer_;
	ComPtr<ID3D11Buffer>		vertex_buffer_;
	ComPtr<ID3D11Buffer>		index_buffer_;
	ComPtr<ID3D11InputLayout>	vertex_layout_;
public:
	Renderable();
	virtual ~Renderable() {};
private:
	void		RegisterComponent();
private:
	HRESULT		CreateVertexBuffer();
	HRESULT		CreateIndexBuffer();
	HRESULT		CreateConstantBuffer();
	HRESULT     CreateVertexLayout();
	void		UpdateConstantBuffer();
public:
	virtual bool		Init();
	bool				Frame();
	bool				Render();
	bool				Release();
protected:
	virtual void		SetVertexData() {};
	virtual void		SetIndexData() {};
};

