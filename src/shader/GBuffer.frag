#version 430 core
layout (location = 0) out vec3 GDiffuse;
layout (location = 1) out vec3 GNormal;
layout (location = 2) out vec3 GPosition;

uniform sampler2D uTexture;

in vec3 fragPos;
in vec2 fragCoord;
in vec3 fragNormal;
void main(){
    GDiffuse = texture(uTexture,fragCoord).xyz;
	GNormal = fragNormal;
	GPosition = fragPos;
}