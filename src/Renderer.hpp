#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <SDL.h>

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

	class Texture* GetTexture(const std::string& file);
	class Mesh* GetMesh(const std::string& fileName);

	float GetScreenWidth() const { return mScreenWidth; }
	float GetScreenHeight() const { return mScreenHeight; }

	void UnloadData();
protected:
	virtual void CreateSpriteVerts();
	virtual bool LoadShaders() { return true; }

	class Game* mGame;
	
	std::unordered_map<std::string, class Texture*> mTextures;
	std::unordered_map<std::string, class Mesh*> mMeshes;
	std::vector<class SpriteComponent*> mSprites;

	class Shader* mSpriteShader;
	class VertexArray* mSpriteVerts;

	float mScreenWidth;
	float mScreenHeight;
	
	SDL_Window* mWindow;
	SDL_GLContext mContext;
};
