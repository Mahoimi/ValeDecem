#version 330 core

in vec2 v_UV;

uniform sampler2D Material;
uniform sampler2D Normal;
uniform sampler2D Depth;
uniform sampler2D Shadow;

uniform vec3 CameraPosition;
uniform vec3 LightDirection;
uniform vec3 LightColor;
uniform float LightIntensity;
uniform mat4 InverseViewProjection;
uniform mat4  LightProjection;
uniform float ShadowBias;
uniform float ShadowSamples;
uniform float ShadowSampleSpread;

vec2 poissonDisk[16] = vec2[](
        vec2( -0.94201624, -0.39906216 ),
        vec2( 0.94558609, -0.76890725 ),
        vec2( -0.094184101, -0.92938870 ),
        vec2( 0.34495938, 0.29387760 ),
        vec2( -0.91588581, 0.45771432 ),
        vec2( -0.81544232, -0.87912464 ),
        vec2( -0.38277543, 0.27676845 ),
        vec2( 0.97484398, 0.75648379 ),
        vec2( 0.44323325, -0.97511554 ),
        vec2( 0.53742981, -0.47373420 ),
        vec2( -0.26496911, -0.41893023 ),
        vec2( 0.79197514, 0.19090188 ),
        vec2( -0.24188840, 0.99706507 ),
        vec2( -0.81409955, 0.91437590 ),
        vec2( 0.19984126, 0.78641367 ),
        vec2( 0.14383161, -0.14100790 )
);

out vec4  Color;

float random(vec4 seed)
{
        float dot_product = dot(seed, vec4(12.9898,78.233,45.164,94.673));
    return fract(sin(dot_product) * 43758.5453);
}

// Lighting with a single directional light
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

	vec3 l =  -LightDirection;

	// Compute the vector from the camera position to the fragment
	vec3 v = position - CameraPosition;

	vec3 h = normalize(l-v);

	float n_dot_l = clamp(dot(n, l), 0, 1.0);
	float n_dot_h = clamp(dot(n, h), 0, 1.0);


	// Final color******************************************************************

	vec3 color = LightColor * LightIntensity * (diffuse * n_dot_l + spec * vec3(1.0, 1.0, 1.0) *  pow(n_dot_h, spec * coeffSpec));


        // Shadows**********************************************************************

        // Projection de la position world en position "light"
        vec4 wlightSpacePosition = LightProjection * vec4(position, 1.0);
        vec3 lightSpacePosition = vec3(wlightSpacePosition/wlightSpacePosition.w);

        // Use the shadow map on area covered by the depth buffer
        if(lightSpacePosition.x > 0.0 && lightSpacePosition.x < 1.0 &&
                lightSpacePosition.y > 0.0 && lightSpacePosition.y < 1.0 &&
                wlightSpacePosition.w  >0.0)
        {

                /* float shadowRead = texture(Shadow, vec2(lightSpacePosition.x, lightSpacePosition.y)).r;

                if(lightSpacePosition.z-shadowRead < ShadowBias) //Lighting
                    Color = vec4(color, 1.0);

                else //Shadow
                    Color = vec4(0.0,0.0,0.0,1.0);*/

                // Percentage Closer Filtering
                float visibility = 1.0;
                float visibilityOffset = 1.0 / ShadowSamples;
                for (int i=0;i<float(ShadowSamples);i++)
                {
                        int index = int(16.0*random(vec4(gl_FragCoord.xyy, i)))%16;
                        float shadowRead = texture(Shadow, lightSpacePosition.xy + poissonDisk[index]/ShadowSampleSpread).r ;
                        if ( shadowRead  + ShadowBias < lightSpacePosition.z  )
                        {
                            visibility-=visibilityOffset;
                        }
                }
                // If visibility = 0 : Shadow, else : Lighting
                Color = vec4(color * visibility, 1.0);

        }

        // Outside the area covered by the depth buffer, use "classic" lighting
        else Color = vec4(color, 1.0);
}
