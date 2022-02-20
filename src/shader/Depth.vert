#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec2 aTex;

uniform mat4 viewProj;
uniform mat4 world;
uniform mat4 lightTransform;
out VS_OUT{
	vec3 fragPos;
	vec3 fragNormal;
	vec2 fragCoord;
	vec4 fragPosLight;
} vs_out;
void main(){
	vec4 pos = vec4(aPos,1.0)*world;
    vs_out.fragPos = pos.xyz;
	gl_Position = pos*viewProj;
	vs_out.fragNormal = aNor * mat3(inverse(transpose(world)));
	vs_out.fragCoord=aTex;
	vs_out.fragPosLight = vec4(vs_out.fragPos,1.0) * lightTransform;
}