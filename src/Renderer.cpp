#include "Game.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"
#include "Mesh.hpp"
#include "MeshComponent.hpp"
#include "Texture.hpp"
#include "SpriteComponent.hpp"

Renderer::Renderer(Game* game)
	:mGame(game)
	, mViewMatrix(Matrix4::Identity)
	, mProjMatrix(Matrix4::Identity)
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
	delete mSpriteVerts;
	delete mSpriteShader;
	delete mMeshShader;
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	for (auto texture : mTextures)
	{
		texture.second->UnLoad();
		delete texture.second;
	}

	for(auto meshes:mMeshes)
	{
		meshes.second->UnLoad();
		delete meshes.second;
	}
	mTextures.clear();
}

void Renderer::SetUniforms(Shader* shader)
{
	Matrix4 invView = mViewMatrix;
	invView.Invert();
	shader->setVec3("ambient", mAmbient);
	shader->setVec3("cameraPos", invView.GetTranslation());
	shader->setFloat("specPower", mSpecPower);

	shader->setVec3("mDirLight.mDirection", mDirLight.mDirection);
	shader->setVec3("mDirLight.mDiffuseColor", mDirLight.mDiffuseColor);
	shader->setVec3("mDirLight.mSpecColor", mDirLight.mSpecColor);
}

void Renderer::Draw()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	mMeshShader->use();
	mMeshShader->setMat4("viewProj", mViewMatrix*mProjMatrix);
	SetUniforms(mMeshShader);
	for(auto comp:mMeshComps)
	{
		comp->Draw(mMeshShader);
	}

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_BLEND_SRC, GL_ONE_MINUS_SRC_ALPHA);

	mSpriteShader->use();
	mSpriteVerts->SetActive();
	for(auto comp:mSprites)
	{
		comp->Draw(mSpriteShader);
	}
	
	SDL_GL_SwapWindow(mWindow);
}

Mesh* Renderer::GetMesh(const std::string& fileName)
{
	const auto meshFromFile = mMeshes.find(fileName);
	if (meshFromFile == mMeshes.end()) {
		auto* mesh = new Mesh();
		mesh->Load(fileName, mGame->GetRenderer());
		mMeshes.insert({ fileName, mesh });
		return mesh;
	}
	return meshFromFile->second;
}

void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

bool Renderer::LoadShaders()
{
	mSpriteShader = new Shader("src/Shader/Sprite.vert", "src/Shader/Sprite.frag");
	mSpriteShader->use();
	Matrix4 viewProj = Matrix4::CreateSimpleViewProj(mScreenWidth, mScreenHeight);
	mSpriteShader->setMat4("viewProj", viewProj);
	
	mMeshShader = new Shader("src/Shader/Basic.vert", "src/Shader/Basic.frag");
	mMeshShader->use();
	mViewMatrix = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	
	mProjMatrix = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.f), mScreenWidth, mScreenHeight, 25.0f, 1000.f);
	mMeshShader->setMat4("viewProj", mViewMatrix*mProjMatrix);
	return true;
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

void Renderer::AddMesh(MeshComponent* mesh)
{
	mMeshComps.emplace_back(mesh);
}

void Renderer::RemoveMesh(MeshComponent* mesh)
{
	auto del = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
	if (del != mMeshComps.end())
		mMeshComps.erase(del);
}
