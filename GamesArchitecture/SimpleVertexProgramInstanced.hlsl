cbuffer cameraBuffer : register(b1)
{
	matrix view;
	matrix projection;
}

struct VS_INPUT
{
	float3 Pos : POSITION;
	float2 TexCoord : TEXCOORD;
	float3 Normal : NORMAL;
	float4 Mat0 : MATRIX0;
	float4 Mat1 : MATRIX1;
	float4 Mat2 : MATRIX2;
	float4 Mat3 : MATRIX3;
};

struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL0;
	float3 FragPos : POSITION0;
};

VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	float4x4 model = float4x4(input.Mat0, input.Mat1, input.Mat2, input.Mat3);

	output.Pos = float4(input.Pos, 1.0f);
	output.Pos = mul(output.Pos, model);

	output.FragPos = output.Pos.xyz;

	output.Pos = mul(view, output.Pos);
	output.Pos = mul(projection, output.Pos);

	output.Normal = input.Normal;

	return output;
}