#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Math.hpp"
#include "Texture.hpp"
#include "Common.hpp"
#include "FrameBuffer.hpp"
#include "MirrorBuffer.hpp"
#include "Model.hpp"

using std::string;
using std::vector;
//phong shader
struct DirectionalLight {
	glm::vec3 mDirection;
	glm::vec3 mDiffuseColor;
	glm::vec3 mSpecColor;
};

struct PointLight {
	Vector3 position;
	Vector3 diffuseColor;
	float inRadius;
	float outRadius;
	Vector3 specColor;
};
class Renderer
{
public:
	Renderer(class Game* game);
	virtual ~Renderer();

	virtual bool Initialize(float width, float height);
	void Shutdown();
	
	virtual void Draw();
	void DrawScene(unsigned int framebuffer,const Matrix4& view,const Matrix4& proj,float viewportScale=1.f);

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMesh(class MeshComponent* sprite);
	void RemoveMesh(class MeshComponent* sprite);

	TexturePtr GetTexture(const std::string& file);
	class Mesh* GetMesh(const std::string& fileName);

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }
	void SetScreenWidth(int width) { mScreenWidth=static_cast<float>(width); }
	void SetScreenHeight(int height) { mScreenHeight=static_cast<float>(height); }

	void UnloadData();
	void SetUniforms(class Shader* shader,Matrix4& view) const;

	Matrix4 GetViewMatrix() const {return mViewMatrix;}
	void SetViewMatrix(const Matrix4& mat) { mViewMatrix = mat; }

	DirectionalLight& GetDirectionalLight() {return mDirLight;}
	void SetDirectionalLight(const DirectionalLight& light) {mDirLight = light;}
	Vector3 GetAmbientLight() const {return mAmbient;}
	void SetAmbientLight(const Vector3& ambient) {mAmbient = ambient;}
	Vector3 GetLightColor() const {return mLightColor;}
	void SetLightColor(const Vector3& color) {mLightColor =color;}

	Vector3 Unproject(const Vector3& screenPoint) const;
	
	PointLight pointLight;
	void AddPointLight(class LightComponent* light);
	void RemovePointLight(class LightComponent* light);

	void setMirrorView(const Matrix4 &view) { mMirrorView = view; }
protected:
	virtual void CreateSpriteVerts();
	virtual bool LoadShaders();
	void DrawFromGBuffer();

	class Game* mGame;
	
	std::unordered_map<std::string, TexturePtr> mTextures;
	std::unordered_map<std::string, class Mesh*> mMeshes;
	std::vector<class SpriteComponent*> mSprites;
	std::vector<class MeshComponent*> mMeshComps;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;

	float mScreenWidth;
	float mScreenHeight;
	
	SDL_Window* mWindow;
	SDL_GLContext mContext;

	Matrix4 mViewMatrix;
	Matrix4 mProjMatrix;
	class Shader* mMeshShader;
	DirectionalLight mDirLight;
	Vector3 mAmbient;
	Vector3 mLightColor;
	const float mSpecPower = 20.f;

	//imgui
	struct ImGuiContext* mImGuiContext;

	//gbuffer
	FrameBufferUPtr mGBuffer;
	class Shader* mGGlobalShader;

	//TODO : fix bug
	//pointlight
	class Shader* mGPointLightShader;
	class Mesh* mPointLightMesh;
	std::vector<class LightComponent*> mLightComponents;

	//mirror
	Matrix4 mMirrorView;
    FrameBufferUPtr mMirrorBuffer;

    //ssao
    FrameBufferUPtr mSsaoBuffer;
    class Shader* mSsaoShader;
    TexturePtr mSsaoNoiseTexture;
    vector<glm::vec3> m_ssaoSamples;
    float mSsaoRadius { 1.0f };
	FrameBufferUPtr mBlurBuffer;
	class Shader* mBlurShader;
	bool useSsao{ true };
};