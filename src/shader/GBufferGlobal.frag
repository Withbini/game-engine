#version 430 core
in vec2 fragCoord;
layout (location=0) out vec4 outColor;

uniform sampler2D gDiffuse;
uniform sampler2D gNormal;
uniform sampler2D gPosition;

uniform vec3 cameraPos;
uniform vec3 ambient;

struct DirectionalLight{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};

uniform DirectionalLight mDirLight;

void main(){
	vec3 gbufferDiffuse = texture(gDiffuse,fragCoord).xyz;
	vec3 gbufferNormal = texture(gNormal,fragCoord).xyz;
	vec3 gbufferWorldPos = texture(gPosition,fragCoord).xyz;

	vec3 N = normalize(gbufferNormal);
	vec3 L = normalize(-mDirLight.mDirection);
	vec3 V = normalize(cameraPos-gbufferWorldPos);
	vec3 R = normalize(reflect(-L,N));
	vec3 H = normalize(L+V);

	float NdotL = dot(N,L);
	vec3 Phong=ambient;
	if(NdotL>0){
		Phong+=NdotL*mDirLight.mDiffuseColor;
	}
	//Phong =clamp(Phong,0.0,1.0);
	outColor =vec4(gbufferDiffuse*Phong,1.0);
}