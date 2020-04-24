struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL0;
	float3 FragPos : POSITION0;
};

float4 main(VS_OUTPUT input) : SV_Target
{
	float3 lightDir = normalize(float3(-100.0f, 100.0f, -100.0f) - input.FragPos);
	float diff = max(dot(input.Normal, lightDir), 0.0f);
	return float4(diff, diff, diff, 1.0f);
}