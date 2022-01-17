#include "openglRenderer.hpp"
#include "SpriteComponent.hpp"
#include "Math.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

openglRenderer::openglRenderer(class Game* game)
	:Renderer(game)
{
}

openglRenderer::~openglRenderer()
{
}

bool openglRenderer::LoadShaders()
{
	mSpriteShader = new Shader("src/shader/Sprite.vert", "src/shader/Sprite.frag");
	mSpriteShader->use();
	const Matrix4 viewProj = Matrix4::CreateSimpleViewProj(GetScreenWidth(), GetScreenHeight());
	mSpriteShader->setMat4("view", viewProj);

	return true;
}

void openglRenderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f,  0.5f, 0.f, 0.f, 0.f,
		 0.5f,  0.5f, 0.f, 1.f, 0.f,
		 0.5f, -0.5f, 0.f, 1.f, 1.f,
		-0.5f, -0.5f, 0.f, 0.f, 1.f
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, indices, 6);
}

void openglRenderer::Draw()
{
	glClearColor(0.86f, 0.86f, 0.86f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mSpriteShader->use();
	mSpriteVerts->SetActive();

	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
}
