#include "Asteroid.hpp"

#include "CircleComponent.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"
#include "Game.hpp"
#include "Random.hpp"

Asteroid::Asteroid(Game* game)
	:Actor(game)
	,mCircle(nullptr)
{
	Vector3 randPos = Random::GetVector(Vector3(-640.0f, -360.0f, 0.f),
		Vector3(640.0f, 360.0f,0.f));
	SetPosition(randPos);
	SetRotation(Quaternion(Vector3::UnitZ,Random::GetFloatRange(0.0f, Math::TwoPi)));

	SpriteComponent* sc = new SpriteComponent(this);
	sc->SetTexture(game->GetRenderer()->GetTexture("Assets/Asteroid.png"));

	// Create a move component, and set a forward speed
	MoveComponent* mc = new MoveComponent(this);
	mc->SetForwardSpeed(100.0f);

	mCircle = new CircleComponent(this);
	mCircle->SetRadius(40.0f);

	// Add to mAsteroids in game
	game->AddAsteroid(this);
}

Asteroid::~Asteroid()
{
	GetGame()->RemoveAsteroid(this);
}
