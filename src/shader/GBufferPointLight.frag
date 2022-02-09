#version 430 core
layout (location=0) out vec4 outColor;

in vec2 texCoord;
uniform sampler2D gDiffuse;
uniform sampler2D gNormal;
uniform sampler2D gPosition;

struct PointLight{
	vec3 position;
	vec3 diffuseColor;
	float inRadius;
	float outRadius;
};
uniform PointLight light;
uniform vec2 screenDimensions;
void main(){
//    vec2 gbufferCoord = gl_FragCoord.xy/ screenDimensions;
//	vec3 gbufferDiffuse = texture(gDiffuse,gbufferCoord).xyz; //이미 그려진 애들의 위치,색상,노멀
//	vec3 gbufferNormal = texture(gNormal,gbufferCoord).xyz;
//	vec3 gbufferPos = texture(gPosition,gbufferCoord).xyz;
//
//	vec3 N = normalize(gbufferNormal);
//	vec3 L = normalize(light.position-gbufferPos);
//	vec3 result=vec3(0.f,0.f,0.f);
//		
//	float distd = distance(light.position, gbufferPos);
//	float intensity = smoothstep(light.inRadius,light.outRadius,distd);
//	vec3 outcolor=mix(light.diffuseColor,vec3(0.f,0.f,0.f),intensity); //입혀지는 라이트색상
//	result = max(dot(N,L),0.f)*outcolor;
//
//	outColor =vec4(gbufferDiffuse*result,1.0);

	vec2 gbufferCoord = gl_FragCoord.xy / screenDimensions;
	
	// Sample from G-buffer
	vec3 gbufferDiffuse = texture(gDiffuse, gbufferCoord).xyz;
	vec3 gbufferNorm = texture(gNormal, gbufferCoord).xyz;
	vec3 gbufferWorldPos = texture(gPosition, gbufferCoord).xyz;
	
	// Surface normal
	vec3 N = normalize(gbufferNorm);
	// Vector from surface to light
	vec3 L = normalize(light.position - gbufferWorldPos);

	// Compute Phong diffuse component for the light
	vec3 Phong = vec3(0.0, 0.0, 0.0);
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		// Get the distance between the light and the world pos
		float dist = distance(light.position, gbufferWorldPos);
		// Use smoothstep to compute value in range [0,1]
		// between inner/outer radius
		float intensity = smoothstep(light.inRadius,
									 light.outRadius, dist);
		// The diffuse color of the light depends on intensity
		vec3 DiffuseColor = mix(light.diffuseColor,
								vec3(0.0, 0.0, 0.0), intensity);
		Phong = DiffuseColor * NdotL;
	}

	// Final color is texture color times phong light (alpha = 1)
	outColor = vec4(gbufferDiffuse * Phong, 1.0);

}