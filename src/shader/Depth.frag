#version 430 core
out vec4 FragColor;
in VS_OUT{
	vec3 fragPos;
	vec3 fragNormal;
	vec2 fragCoord;
	vec4 fragPosLight;
} fs_in;

struct DirectionalLight{
	vec3 direction;
	vec3 diffuseColor;
	vec3 specColor;
};
uniform DirectionalLight dirLight;
uniform vec3 ambient;
uniform vec3 cameraPos;
uniform float specPower;
uniform sampler2D uTexture0;
uniform sampler2D shadowMap;


float CalculateShadow(vec4 fragPosLight,vec3 normal, vec3 lightDir){
	vec3 projCoords = fragPosLight.xyz / fragPosLight.w;
    // transform to [0,1] range
	projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture(shadowMap, projCoords.xy).r;
    float currentDepth = projCoords.z;
    // check whether current frag pos is in shadow
    float bias = max(0.01 * (1.0 - dot(normal, lightDir)), 0.001);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x) {
        for (int y = -1; y <= 1; ++y) {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;
        }
    }
    shadow /= 9.0;
    return shadow;
}

void main(){
	vec3 N = normalize(fs_in.fragNormal);
    vec3 L = normalize(-dirLight.direction);
	vec3 V = normalize(cameraPos-fs_in.fragPos);
	vec3 R = normalize(reflect(-L,N));
	vec3 H = normalize(L+V);

	vec3 diffuse = max(0.0,dot(N,L)) * dirLight.diffuseColor;
	vec3 specular= pow(max(0.0,dot(H,N)),specPower) * dirLight.specColor;
	float shadow = CalculateShadow(fs_in.fragPosLight,N,dirLight.direction);
	vec3 Phong = (diffuse + specular)*(1.0-shadow) + ambient*texture(uTexture0, fs_in.fragCoord).xyz;
	FragColor = vec4(Phong,1.0);
}