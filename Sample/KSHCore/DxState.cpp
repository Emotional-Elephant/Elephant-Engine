#include "DxState.h"
ID3D11SamplerState* DxState::g_pDefaultSSWrap = nullptr;
ID3D11SamplerState* DxState::g_pDefaultSSMirror = nullptr;

ID3D11RasterizerState* DxState::g_pDefaultRSWireFrame = nullptr;
ID3D11RasterizerState* DxState::g_pDefaultRSSolid = nullptr;

ID3D11BlendState* DxState::g_pAlphaBlend = nullptr;

bool DxState::SetState(ID3D11Device* pd3dDevice)
{
	HRESULT hr;
	// SS
	D3D11_SAMPLER_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT; // �ֱ��� ���͸�
	sd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	hr = pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSWrap);
	if (FAILED(hr))
	{
		return false;
	}

	sd.Filter = D3D11_FILTER_MIN_MAG_POINT_MIP_LINEAR;
	sd.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
	sd.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
	hr = pd3dDevice->CreateSamplerState(&sd, &g_pDefaultSSMirror);
	if (FAILED(hr))
	{
		return false;
	}

	D3D11_RASTERIZER_DESC rd;
	ZeroMemory(&rd, sizeof(rd));
	rd.DepthClipEnable = TRUE;
	rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.CullMode = D3D11_CULL_NONE;
	pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSWireFrame);

	rd.FillMode = D3D11_FILL_SOLID;
	pd3dDevice->CreateRasterizerState(&rd, &g_pDefaultRSSolid);

	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	//bd.IndependentBlendEnable = TRUE;
	// ȥ�� : ���´�.
	// ���(������) d-RGBA : ����ۿ� �̹� ������ �Ǿ� �ִ� ���
	// ���� �ҽ� : s_RGBA : ���� ������ �Ϸ��� ��ü, �ȼ����̴�
	// RGB ������ ȥ���ϴ� ���
	// ���ĺ��� ����
	// finalColor = SrcColor*SrcAlpha+DestColor*(1.0f-SrcApha);
	// apha = 1.0f (������), alpha = 0.0f (����), alpha 0-1 (������)
	// finalColor = SrcColor*1.0f+DestColor*(1.0f-1.0f);
	// finalColor = SrcColor*0.0f+DestColor*(1.0f-0.0f);
	// finalColor = SrcColor*0.5f+DestColor*(1.0f-0.5f);
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	bd.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	// ���� ������ ȥ���ϴ� ���
	// finalAlpha = SrcAlpha*1.0f+DestAlpha*0.0f;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	pd3dDevice->CreateBlendState(&bd, &g_pAlphaBlend);

	return true;
}

bool DxState::Release()
{
	if (g_pDefaultSSWrap) g_pDefaultSSWrap->Release();
	if (g_pDefaultSSMirror) g_pDefaultSSMirror->Release();
	if (g_pDefaultRSWireFrame) g_pDefaultRSWireFrame->Release();
	if (g_pDefaultRSSolid) g_pDefaultRSSolid->Release();
	if (g_pAlphaBlend) g_pAlphaBlend->Release();

	g_pDefaultSSWrap = nullptr;
	g_pDefaultSSMirror = nullptr;
	g_pDefaultRSWireFrame = nullptr;
	g_pDefaultRSSolid = nullptr;
	g_pAlphaBlend = nullptr;
	return true;
}