struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float3 Normal : NORMAL0;
	float3 FragPos : POSITION0;
};

cbuffer pointLightBuffer : register(b2)
{
	float3 lightPosition;
	float3 lightColour;
}

float4 main(VS_OUTPUT input) : SV_Target
{
	float3 lightDir = normalize(lightPosition - input.FragPos);
	float diff = max(dot(input.Normal, lightDir), 0.0f);

	if ((floor(input.FragPos.x * 10.0f) + floor(input.FragPos.z * 10.0f)) % 2)
	{
		diff *= 0.5f;
	}

	return float4(lightColour * diff, 1.0f);
}