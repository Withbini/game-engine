#version 430 core
out vec4 fragColor;
struct DirectionalLight{
	vec3 direction;
	vec3 diffuseColor;
	vec3 specColor;
};
uniform sampler2D uTexture0;
uniform sampler2D uTexture1;
uniform vec3 ambient;
uniform vec3 lightColor;
uniform vec3 cameraPos;
uniform float specPower;

uniform DirectionalLight dirLight;

in vec2 fragCoord;
in vec3 fragNormal;
in vec3 fragPos;

void main(){
	vec3 N = normalize(fragNormal);
    vec3 L = normalize(-dirLight.direction);
	vec3 V = normalize(cameraPos-fragPos);
	vec3 R = normalize(reflect(-L,N));

	//vec3 diffuse = max(0.f,dot(N,L)) * dirLight.mDiffuseColor;
	//vec3 specular= pow(max(0.0,dot(V,R)),specPower) * dirLight.mSpecColor;
	//vec3 Phong = diffuse + specular + ambient;
	vec3 diffuseColor = texture(uTexture0,fragCoord).xyz;
	vec3 specularColor = texture(uTexture1,fragCoord).xyz;
	vec3 Phong = ambient*diffuseColor;
	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		vec3 Diffuse = dirLight.diffuseColor * NdotL*diffuseColor;
		vec3 Specular = dirLight.specColor * pow(max(0.0, dot(R, V)), specPower)*specularColor;
		Phong += Diffuse + Specular;
	}

	fragColor = vec4(Phong,1.0f);
}