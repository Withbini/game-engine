#version 430 core
out vec4 FragColor;
struct DirectionalLight{
	vec3 mDirection;
	vec3 mDiffuseColor;
	vec3 mSpecColor;
};
uniform sampler2D uTexture;
uniform vec3 ambient;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform float specPower;

uniform DirectionalLight mDirLight;

in vec2 fragCoord;
in vec3 fragNormal;
in vec3 fragPos;


void main(){
	vec3 N = normalize(fragNormal);
    vec3 L = normalize(-mDirLight.mDirection);
	vec3 V = normalize(cameraPos-fragPos);
	vec3 R = normalize(reflect(-L,N));
	vec3 H = normalize(L+V);

	vec3 diffuse = max(0.f,dot(N,L)) * mDirLight.mDiffuseColor;
	vec3 specular= pow(max(0.0,dot(N,H)),specPower) * mDirLight.mSpecColor;
	vec3 Phong = diffuse + specular + ambient;

	FragColor = texture(uTexture,fragCoord)*vec4(Phong,1.0f);
}