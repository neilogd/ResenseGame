uniform sampler2D aDiffuseTex;

vec4 shaderMain()
{
	return texture( aDiffuseTex, vTexCoord0.xy );
}
