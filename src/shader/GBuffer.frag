#version 430 core
layout (location = 0) out vec3 GDiffuse;
layout (location = 1) out vec3 GNormal;
layout (location = 2) out vec3 GPosition;
layout (location = 3) out vec3 GSpecular;
uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

in vec3 fragPos;
in vec2 fragCoord;
in vec3 fragNormal;
void main(){
    GDiffuse = texture(uTexture0,fragCoord).xyz;
	GSpecular = texture(uTexture1,fragCoord).xyz;
	GNormal = fragNormal;
	GPosition = fragPos;
}