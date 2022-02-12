#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Math.hpp"
#include "Texture.hpp"
#include "Common.hpp"
#include "FrameBuffer.hpp"

using std::string;
using std::vector;
//phong shader
struct DirectionalLight {
	glm::vec3 mDirection;
	glm::vec3 mDiffuseColor;
	Vector3 mSpecColor;
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

	//temp
	Matrix4 mMirrorView;
	FrameBufferUPtr mMirrorBuffer;
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
	float mSpecPower = 20.f;

	//imgui
	struct ImGuiContext* mImGuiContext;

	//gbuffer
	class GBuffer* mGBuffer;
	class Shader* mGGlobalShader;

	//pointlight
	class Shader* mGPointLightShader;
	class Mesh* mPointLightMesh;
	std::vector<class LightComponent*> mLightComponents; //temporary
};