#pragma once
#include "stdafx.h"

struct VS_CONSTANT_BUFFER_CAMERA
{
	TMatrix		view_matrix_;
	TMatrix		proj_matrix_;
};


class Camera
{
protected:
	TVector3			position_;
	TVector3			target_;
	const TVector3		up_ = { 0.0f, 1.0f, 0.0f };
protected:
	float				near_plane_dist_;
	float				far_plane_dist_;
	float				field_of_view_;
	float				aspect_;
private:
	VS_CONSTANT_BUFFER_CAMERA	constant_buffer_data_;
	ComPtr<ID3D11Buffer>		constant_buffer_;
private:
	HRESULT			CreateConstantBuffer();
public:
	bool			Init();
public:
	virtual bool	SetValues() = 0;
	virtual bool	Frame() = 0;
	virtual bool	Render();
	virtual bool	Release();
};