#version 430 core
out vec4 FragColor;

uniform sampler2D uTexture;

in vec2 fragCoord;
void main(){
	FragColor = texture(uTexture, fragCoord);
}