out vec3 vEyePosition;
out vec4 vWorldPosition;

vec4 shaderMain(vec4 inPosition)
{
	vEyePosition.x = uInverseViewTransform[3][0];
	vEyePosition.y = uInverseViewTransform[3][1];
	vEyePosition.z = uInverseViewTransform[3][2];
	vWorldPosition = uWorldTransform * aPosition;
	vTexCoord0 = aTexCoord0;

	return inPosition;
}
