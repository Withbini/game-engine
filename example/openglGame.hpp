#pragma once
#include "Game.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
#include "Renderer.hpp"

class openglGame :
	public Game
{
public:
	openglGame();
	~openglGame() override;
	bool Initialize() override;
	void LoadData() override;

private:
	class Ship2* mShip;

	VertexArray* mSpriteVerts;
	int mSpriteFrags;
	Shader* mSpriteShader;
};

