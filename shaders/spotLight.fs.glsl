#version 330 core

in vec2 v_UV;

uniform sampler2D Material;
uniform sampler2D Normal;
uniform sampler2D Depth;

uniform vec3 CameraPosition;
uniform vec3  LightPosition;
uniform vec3 LightDirection;
uniform vec3 LightColor;
uniform float LightIntensity;
uniform mat4 InverseViewProjection;

out vec4  Color;

// Lighting with a single spot light
void main(void)
{
	// Fragment characteristics*****************************************************

	// Retrieve the fragment characteristics from the provided textures
	vec4  material = texture(Material, v_UV).rgba;
	vec3  normal = texture(Normal, v_UV).rgb;
	float depth = texture(Depth, v_UV).r;
	
	// Compute the fragment position thanks to the depth information
	vec2 xy = v_UV * 2.0 -1.0;
	vec4 wPosition = vec4(xy, depth * 2.0 -1.0, 1.0) * InverseViewProjection;
	vec3 position = vec3(wPosition/wPosition.w);

	// Compute the others characteristics of the fragment
	vec3 diffuse = material.rgb;
	float spec = texture(Normal, v_UV).a;
	vec3 n = normalize(normal);
	
	float coeffSpec = 100.0;


	// Light and fragment***********************************************************

	// Compute the vector from the fragment to the light source (surfaceToLight)
	vec3 l =  LightPosition - position;

	// Compute the vector from the camera position to the fragment
	vec3 v = position - CameraPosition;

	vec3 h = normalize(l-v);

	float n_dot_l = clamp(dot(n, l), 0, 1.0);
	float n_dot_h = clamp(dot(n, h), 0, 1.0);

	// Angle between the vector from the fragment to the light source (surfaceToLight) and the direction of the light
	float cosAngleLD = dot(normalize(l), -normalize(LightDirection));

	float spotAngle = radians(45.0);
	float fallOffAngle = radians(30.0);


	// Final color******************************************************************
	
	vec3 color = vec3(0);
	
	// If the angle between the vectors surfaceToLight and LightDirection (cosAngleLD) is smaller than spotAngle, then the fragment is lighted by the spot
	if(cosAngleLD > cos(spotAngle)){
		float falloff = 1.0f;
		// If the angle between the vectors surfaceToLight and LightDirection is bigger than fallOffAngle, then there is an attenuation
		if(cosAngleLD < cos(fallOffAngle)){
			falloff = pow( (cosAngleLD - cos(spotAngle)) /  (cos(fallOffAngle) - cos(spotAngle)) , 4);
		}
		color =  falloff * LightColor * LightIntensity * (diffuse * n_dot_l + spec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, spec * coeffSpec));
	}
	
	Color = vec4(color, 1.0);
}