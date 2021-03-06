#version 430 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNor;
layout(location = 2) in vec2 aTex;

uniform mat4 viewProj;
uniform mat4 world;

out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragCoord;
void main(){
	vec4 pos = vec4(aPos,1.0)*world;
    fragPos = pos.xyz;
	gl_Position = pos*viewProj;
	//fragNormal = aNor * mat3(inverse(transpose(world)));
	fragNormal = (vec4(aNor, 0.0f) * world).xyz;
	fragCoord=aTex;
}