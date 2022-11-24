struct VS_in
{
	float3 position : POSITION;
	float4 color : COLOR;
	float2 tex : TEXTURE;
};
struct VS_out
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};

VS_out VS(VS_in input) 
{
	VS_out output = (VS_out)0;
    	output.p = float4(input.position, 1.0f);
	output.c = input.color;
	output.t = input.tex;
	return output;
}