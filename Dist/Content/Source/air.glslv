out vec3 vEyePosition;
out vec4 vWorldPosition;

vec4 shaderMain(vec4 inPosition)
{
	vEyePosition.x = uInverseViewTransform[0][3];
	vEyePosition.y = uInverseViewTransform[1][3];
	vEyePosition.z = uInverseViewTransform[2][3];
	vWorldPosition = uWorldTransform * aPosition;
	vTexCoord0 = aTexCoord0;

	return inPosition;
}
