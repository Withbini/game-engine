#include "Asteroid.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "Random.hpp"
//#include "CircleComponent.hpp"

Asteroid::Asteroid(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{
	Vector2 randPos = Random::GetVector(Vector2::Zero,
		Vector2(1280.0f, 720.0f));
	SetPosition(randPos);
	SetRotation(Random::GetFloatRange(0.0f, Math::TwoPi));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetTexture("Assets/Asteroid.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(100.0f);

	// Create a circle component (for collision)
	//mCircle = new CircleComponent(this);
	//mCircle->SetRadius(40.0f);

	// Add to mAsteroids in game
	//game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	//GetGame()->RemoveAsteroid(this);
}
