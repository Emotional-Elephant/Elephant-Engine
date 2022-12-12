Texture2D g_txTex : register(t0);
SamplerState g_SampleWrap : register(s0);

struct PS_input
{
	float4 p : SV_POSITION;
    float3 n : NORMAL;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
    float4 lightcolor : TEXCOORD1;
};
float4 PS(PS_input input) : SV_Target
{
    return input.c;
}