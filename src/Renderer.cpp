#include "Renderer.hpp"

#include "Mesh.hpp"
#include "Texture.hpp"
#include "SpriteComponent.hpp"
#include "Game.hpp"
Renderer::Renderer(Game* game)
	:mGame(game)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(float width, float height)
{
	mScreenWidth = width;
	mScreenHeight = height;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("Game Programming", 100, 100, static_cast<int>(mScreenWidth), static_cast<int>(mScreenHeight), SDL_WINDOW_OPENGL);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	mContext = SDL_GL_CreateContext(mWindow);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	glGetError();

	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}

	CreateSpriteVerts();

	return true;
}

void Renderer::Shutdown()
{
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	for (auto texture : mTextures)
	{
		delete texture.second;
	}
	mTextures.clear();
}

void Renderer::Draw()
{
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	const auto meshFromFile = mMeshes.find(fileName);
	if (meshFromFile == mMeshes.end()) {
		auto* mesh = new Mesh();
		mesh->Load(fileName, mGame);
		mMeshes.insert({ fileName, mesh });
		return mesh;
	}
	return meshFromFile->second;
}

void Renderer::CreateSpriteVerts()
{
}

Texture* Renderer::GetTexture(const std::string& fileName)
{
	const auto textureFromFile = mTextures.find(fileName);
	if (textureFromFile == mTextures.end()) {
		auto* texture = new Texture();
		texture->Load(fileName);
		mTextures.insert({ fileName, texture });
		return texture;
	}
	return textureFromFile->second;
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	const int drawOrder = sprite->GetDrawOrder();
	auto it = mSprites.begin();
	for (; it != mSprites.end(); ++it)
	{
		if (drawOrder < (*it)->GetDrawOrder())
		{
			break;
		}
	}
	mSprites.insert(it, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto delSprite = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(delSprite);
}