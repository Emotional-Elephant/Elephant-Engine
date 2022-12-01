#pragma once
#include "stdafx.h"

struct VS_CONSTANT_BUFFER_CAMERA
{
	TMatrix		view_matrix_;
	TMatrix		proj_matrix_;
};


class Camera
{
private:
	TVector3			m_vPosition;
	TVector3			m_vTarget;
	const TVector3		m_vUp = { 0.0f, 1.0f, 0.0f };
private:
	float				m_fNearPlane;
	float				m_fFarPlane;
	float				m_fovy;
	float				m_Aspect;
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