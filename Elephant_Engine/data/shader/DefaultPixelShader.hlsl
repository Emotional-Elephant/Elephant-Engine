struct PS_input
{
	float4 p : SV_POSITION;
	float4 c : COLOR0;
	float2 t : TEXCOORD0;
};
float4 PS(PS_input input) : SV_Target
{
    return input.c;
}