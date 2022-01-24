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
	Renderer::LoadShaders();
	mSpriteShader = new Shader("src/shader/Sprite.vert", "src/shader/Sprite.frag");
	mSpriteShader->use();
	const Matrix4 viewProj = Matrix4::CreateSimpleViewProj(GetScreenWidth(), GetScreenHeight());
	mSpriteShader->setMat4("view", viewProj);

	return true;
}

void openglRenderer::CreateSpriteVerts()
{
	Renderer::CreateSpriteVerts();
}

void openglRenderer::Draw()
{
	Renderer::Draw();
	
	//especially sprite
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mSpriteShader->use();
	mSpriteVerts->Bind();

	for (auto sprite : mSprites)
	{
		sprite->Draw(mSpriteShader);
	}

	SDL_GL_SwapWindow(mWindow);
}
