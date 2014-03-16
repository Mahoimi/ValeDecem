#version 330 core

in vec2 v_UV;

uniform sampler2D Material;

uniform vec3 LightColor;
uniform float LightIntensity;

out vec4  Color;

// Lighting with a single directional light
void main(void)
{
	// Fragment characteristics*****************************************************

	// Retrieve the fragment characteristics from the provided textures
	vec4  material = texture(Material, v_UV).rgba;

	// Compute the others characteristics of the fragment
	vec3 diffuse = material.rgb;


	// Final color******************************************************************

        vec3 color = LightColor * LightIntensity * diffuse;
	Color = vec4(color, 1.0);
}
