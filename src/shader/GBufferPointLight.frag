#version 430 core
in vec2 fragCoord;
layout (location=0) out vec4 outColor;

uniform sampler2D gDiffuse;
uniform sampler2D gNormal;
uniform sampler2D gPosition;

uniform vec3 cameraPos;
uniform vec3 ambient;

struct PointLight{
	vec3 position;
	vec3 diffuseColor;
	vec3 specColor;
};
const int lightCount=32;
uniform PointLight light[32];

void main(){
	vec3 gbufferDiffuse = texture(gDiffuse,fragCoord).xyz;
	vec3 gbufferNormal = texture(gNormal,fragCoord).xyz;
	vec3 gbufferPos = texture(gPosition,fragCoord).xyz;

	vec3 N = normalize(gbufferNormal);
	vec3 V = normalize(cameraPos-gbufferPos);
	vec3 result;
	for(int i=0;i<lightCount;++i){
		vec3 L = normalize(light[i].position-gbufferPos);
		vec3 R = normalize(reflect(-L,N));
		vec3 H = normalize(L+V);
		vec3 Phong=ambient;
		Phong+=max(dot(N,L),0.0f)*light[i].diffuseColor;
		result+=Phong;
	}

	//Phong =clamp(Phong,0.0,1.0);
	outColor =vec4(gbufferDiffuse*result,1.0);
}