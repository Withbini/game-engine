#pragma once
#include "Renderer.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"

class openglRenderer:
public Renderer
{
public:
	openglRenderer(class Game* game);
	~openglRenderer() override;
private:
	bool LoadShaders() override;
	void CreateSpriteVerts() override;

	class Ship2* mShip;
	void Draw() override;

	int mSpriteFrags;
	Shader* mSpriteShader;
};
