#version 430 core
layout (location = 0) out vec4 gAlbedoSpec;
layout (location = 1) out vec4 gNormal;
layout (location = 2) out vec4 gPosition;
uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

in vec3 fragPos;
in vec2 fragCoord;
in vec3 fragNormal;
void main(){
    gAlbedoSpec.rgb = texture(uTexture0,fragCoord).rgb;
	gAlbedoSpec.a = texture(uTexture1,fragCoord).r;
	gNormal = vec4(normalize(fragNormal),1.0);
	gPosition = vec4(fragPos,1.0);
}