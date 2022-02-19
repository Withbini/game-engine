#version 430 core
out vec4 fragColor;
in vec2 fragCoord;
uniform sampler2D tex;
void main(){
	vec2 texSize = 1.0 / vec2(textureSize(tex , 0));
	vec4 result = vec4(0.0);
	for(int i = -2; i <= 2; ++i){
		for(int j = -2; j <= 2; ++j){
			vec2 offset = vec2(float(i), float(j)) * texSize;
			result += texture(tex, fragCoord + offset);
		}
	}
	fragColor = result / 25.0;
}