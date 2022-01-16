#include "openglGame.hpp"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#endif

#include "Asteroid.hpp"
#include "BGSpriteComponent.hpp"
#include "Ship2.hpp"

openglGame::openglGame()
	: mSpriteShader(nullptr)
	, mSpriteVerts(nullptr)
{
}

openglGame::~openglGame()
{
	delete mSpriteVerts;
	delete mSpriteShader;
}

bool openglGame::Initialize()
{
	Game::Initialize();
	stbi_set_flip_vertically_on_load(true);
	LoadShaders();
	CreateSpriteVerts();
	LoadData();
	

	return true;
}

void openglGame::LoadData()
{
	mShip = new Ship2(this);
	mShip->SetPosition(Vector2(0.f, 0.0f));
	mShip->SetScale(1.5f);

	const int numAsteriod = 20;
	for (int i = 0; i < numAsteriod; ++i)
	{
		new Asteroid(this);
	}
}

bool openglGame::LoadShaders()
{
	mSpriteShader = new Shader("src/shader/Sprite.vert", "src/shader/Sprite.frag");
	mSpriteShader->use();
	const Matrix4 viewProj = Matrix4::CreateSimpleViewProj(WINDOW_WIDTH, WINDOW_HEIGHT);
	mSpriteShader->setMat4("view", viewProj);

	return true;
}

void openglGame::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f, // top left
		 0.5f,  0.5f, 0.f, 1.f, 0.f, // top right
		 0.5f, -0.5f, 0.f, 1.f, 1.f, // bottom right
		-0.5f, -0.5f, 0.f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void openglGame::GenerateOutput()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	mSpriteShader->use();
	mSpriteVerts->SetActive();

	for (auto* sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
	return;
}
