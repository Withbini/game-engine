#version 430 core
in vec2 fragCoord;
layout (location=0) out vec4 outColor;

layout (binding=0)uniform sampler2D gAlbedoSpec;
layout (binding=1)uniform sampler2D gNormal;
layout (binding=2)uniform sampler2D gPosition;
layout (binding=3)uniform sampler2D ssao;
uniform int useSSAO;

uniform vec3 cameraPos;
//uniform vec3 ambient;

struct DirectionalLight{
	vec3 direction;
	vec3 diffuseColor;
	vec3 specColor;
};
uniform float specPower;
uniform DirectionalLight dirLight;

void main(){
	vec3 gbufferDiffuse = texture(gAlbedoSpec,fragCoord).rgb;
	vec3 gbufferNormal = texture(gNormal,fragCoord).rgb;
	vec3 gbufferWorldPos = texture(gPosition,fragCoord).rgb;

	vec3 N = normalize(gbufferNormal);
	vec3 L = normalize(-dirLight.direction);
	vec3 V = normalize(cameraPos-gbufferWorldPos);
	vec3 R = normalize(reflect(-L,N));
	vec3 H = normalize(L+V);
	float specular = texture(gAlbedoSpec,fragCoord).a;
	
	float NdotL = dot(N,L);
	vec3 ambient= useSSAO == 1 ? texture(ssao, fragCoord).r *0.4*gbufferDiffuse : gbufferDiffuse*0.4;
	vec3 Phong=ambient;
	Phong+=max(dot(N,L),0.0f)*dirLight.diffuseColor*gbufferDiffuse;
	Phong+=pow(max(dot(N,H),0.0),specPower)*dirLight.specColor*specular;
	outColor =vec4(Phong,1.0);
}