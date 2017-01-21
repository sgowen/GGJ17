cbuffer OffsetBuffer : register(b0)
{
	float offset;
};

Texture2D Texture;
SamplerState ss;

// Pixel Shader
float4 main(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	texcoord.x += sin(texcoord.y * 4.0 * 2.0 * 3.14159 + offset) / 100.0;
	return color * Texture.Sample(ss, texcoord);
}