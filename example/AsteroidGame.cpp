#include "AsteroidGame.hpp"
#include "Asteroid.hpp"
#include "BGSpriteComponent.hpp"
#include "Ship2.hpp"

void AsteroidGame::LoadData()
{
	mShip = new Ship2(this);
	mShip->SetPosition(Vector2(512.f, 384.0f));
	mShip->SetScale(1.5f);
	
	const int numAsteriod = 20;
	for(int i=0;i< numAsteriod;++i)
	{
		new Asteroid(this);
	}
}
