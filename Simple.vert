#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec2 aTex;

uniform mat4 viewProj;
uniform mat4 world;
void main(){
	vec4 pos = vec4(aPos,1.0)*world;
	gl_Position = pos*viewProj;
}