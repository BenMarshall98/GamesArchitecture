cbuffer modelBuffer : register(b0)
{
	matrix model;
}

cbuffer cameraBuffer : register(b1)
{
	matrix view;
	matrix projection;
}

struct VS_INPUT
{
	float3 Pos : POSITION;
	//float2 TexCoord : TEXCOORD;
	//float3 Normal : NORMAL;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
};

VS_OUTPUT main(VS_INPUT input, uint instanceID : SV_InstanceID)
{
	VS_OUTPUT output = (VS_OUTPUT) 0;

	output.Pos = float4(input.Pos, 1.0f);
    output.Pos = output.Pos + instanceID * float4(-1.0f, -1.0f, -1.0f, 0.0f);
	output.Pos = mul(output.Pos, model);
	output.Pos = mul(output.Pos, view);
	output.Pos = mul(output.Pos, projection);

	return output;
}