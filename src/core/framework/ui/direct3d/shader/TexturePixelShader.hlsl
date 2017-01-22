Texture2D Texture;
SamplerState ss;

// Pixel Shader
float4 main(float4 position : SV_POSITION, float4 color : COLOR, float2 texcoord : TEXCOORD) : SV_TARGET
{
	float4 ret = Texture.Sample(ss, texcoord);

	if (ret.a > 0.0
		&& color.g < 1.0)
	{
		float redness = color.r * 2.0;
		redness = clamp(color.r, 0.0, 1.0);
		float rDelta = 1.0 - ret.r;
		ret.r += rDelta * redness;
		ret.r = clamp(ret.r, 0.0, 1.0);

		if (color.r > 0.5)
		{
			float additive = (color.r - 0.5) * 2.0;

			float gDelta = 1.0 - ret.g;
			float bDelta = 1.0 - ret.b;

			ret.g += gDelta * additive;
			ret.g = clamp(ret.g, 0.0, 1.0);

			ret.b += bDelta * additive;
			ret.b = clamp(ret.b, 0.0, 1.0);
		}
	}

    ret.a *= color.a;

	return ret;
}
