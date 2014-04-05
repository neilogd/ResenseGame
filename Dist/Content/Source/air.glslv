out vec3 vEyePosition;
out vec4 vWorldPosition;

vec4 shaderMain(vec4 inPosition)
{
	vEyePosition = uInverseViewTransform[3].xyz;
	vWorldPosition = uWorldTransform * aPosition;
	vTexCoord0 = aTexCoord0;

	return inPosition;
}
