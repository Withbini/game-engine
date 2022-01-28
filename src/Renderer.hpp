#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <SDL.h>
#include "Math.hpp"

//phong shader
struct DirectionalLight {
	Vector3 mDirection;
	Vector3 mDiffuseColor;
	Vector3 mSpecColor;
};

class Renderer
{
public:
	Renderer(class Game* game);
	virtual ~Renderer();

	virtual bool Initialize(float width, float height);
	void Shutdown();
	
	virtual void Draw();

	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);

	void AddMesh(class MeshComponent* sprite);
	void RemoveMesh(class MeshComponent* sprite);

	class Texture* GetTexture(const std::string& file);
	class Mesh* GetMesh(const std::string& fileName);

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

	void UnloadData();
	void SetUniforms(class Shader* shader) const;

	Matrix4 GetViewMatrix() const {return mViewMatrix;}
	//Matrix4 GetProjMatrix() const {return mProjMatrix;}
	void SetViewMatrix(const Matrix4& mat) { mViewMatrix = mat; }
	//void SetProjMatrix(const Matrix4& mat) { mProjMatrix = mat; }

	DirectionalLight& GetDirectionalLight() {return mDirLight;}
	void SetDirectionalLight(const DirectionalLight& light) {mDirLight = light;}
	Vector3 GetAmbientLight() const {return mAmbient;}
	void SetAmbientLight(const Vector3& ambient) {mAmbient = ambient;}
	Vector3 GetLightColor() const {return mLightColor;}
	void SetLightColor(const Vector3& color) {mLightColor =color;}
protected:
	virtual void CreateSpriteVerts();
	virtual bool LoadShaders();

	class Game* mGame;
	
	std::unordered_map<std::string, class Texture*> mTextures;
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
};