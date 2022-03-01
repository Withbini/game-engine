#version 430 core
out float fragColor;

uniform sampler2D gAlbedoSpec;
uniform sampler2D gNormal;
uniform sampler2D gPosition;
uniform sampler2D texNoise; //�������� ���� �̹���

uniform mat4 view;
uniform mat4 proj;
uniform vec2 noiseScale;
uniform float radius;

const int KERNEL_SIZE = 64;
const float bias  = 0.025;
uniform vec3 samples[KERNEL_SIZE];

in vec2 fragCoord; //�޽� vertex���� texture ��ǥ
void main(){
	vec4 worldPos = texture(gPosition,fragCoord);
	if(worldPos.w <= 0.0)
		discard;
	vec3 fragPos = (view * vec4(worldPos.xyz, 1.0)).xyz;
	vec3 normal = (view * vec4(texture(gNormal, fragCoord).xyz, 0.0)).xyz;
	vec3 randomVec = texture(texNoise, fragCoord * noiseScale).xyz;
 
	vec3 tangent = normalize(randomVec - normal * dot(randomVec, normal));
	vec3 bitangent = cross(normal, tangent);
	mat3 TBN = mat3(tangent, bitangent, normal);

	float occlusion = 0.0;
	for(int i = 0; i < KERNEL_SIZE; ++i){
		//vec3 sample1 = fragPos +TBN * samples[i] * radius; //ī�޶�������� fragment ��ǥ���ٰ� �Ϻ� ����
		vec3 sample1 = fragPos;
		vec4 screenSample = proj * vec4(sample1, 1.0); //��ũ�� ���� ��ǥ
		screenSample.xyz /= screenSample.w;
		screenSample.xyz = screenSample.xyz * 0.5 + 0.5;

		float sampleDepth = (view * texture(gPosition, screenSample.xy)).z; //ī�޶󿡼� �ٶ� depth 
		//ssao�� ���ø��� ���� ���� �ֺ��� depth�� ���ϴ°��̱� ����?
		float rangeCheck = smoothstep(0.0, 1.0, radius / abs(fragPos.z - sampleDepth));
		occlusion += (sampleDepth >= sample1.z + bias ? 1.0 : 0.0) * rangeCheck;
	}
	fragColor = 1.0 - occlusion / KERNEL_SIZE;
	fragColor=tangent.x;
}