#version 430 core
layout(location = 0) out vec4 outColor;

in vec2 fragCoord;
uniform sampler2D gAlbedoSpec;
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
    vec2 gbufferCoord = gl_FragCoord.xy/ screenDimensions; //화면상의 좌표를 가져옴
	vec3 gbufferDiffuse = texture(gAlbedoSpec,gbufferCoord).xyz; //이미 그려진 애들의 위치,색상,노멀
	vec3 gbufferNormal = texture(gNormal,gbufferCoord).xyz;
	vec3 gbufferPos = texture(gPosition,gbufferCoord).xyz;

	vec3 N = normalize(gbufferNormal);
	vec3 L = normalize(light.position-gbufferPos);
	vec3 result=vec3(0.0,0.0,0.0);
		
	float distd = distance(light.position, gbufferPos);
	float intensity = smoothstep(light.inRadius, light.outRadius, distd);
	vec3 outcolor= mix(light.diffuseColor,vec3(0.0,0.0,0.0),intensity); //입혀지는 라이트색상
	result = max(dot(N,L),0.0)*outcolor;
	result= vec3(1,0,0);
	outColor =vec4(gbufferDiffuse*result,1.0);
}