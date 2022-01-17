#version 430 core
out vec4 FragColor;
uniform sampler2D Tex;
in vec2 texCoord;
void main(){
	//FragColor = texture(Tex, texCoord);
	FragColor = vec4(0.0,0.0,1.0,1.0);
}