#version 430 core
layout (location = 0) out vec3 aPos;
layout (location = 1) out vec3 aNor;
layout (location = 2) out vec2 aTex;
uniform mat4 world;
uniform mat4 viewProj;

out vec2 fragCoord;
void main(){
	vec4 pos = vec4(aPos, 1.0);
	gl_Position = pos * world * viewProj;
	fragCoord = aTex;
}