#include "Laser.hpp"
#include "AsteroidGame.hpp"
#include "CircleComponent.hpp"
#include "SpriteComponent.hpp"
#include "MoveComponent.hpp"

Laser::Laser(Game* game)
	:Actor(game)
	,mCircle(new CircleComponent(this))
	,mDeathTimer(1.f)
{
	// Create an animated sprite component
	auto* asc = new SpriteComponent(this);
	asc->SetTexture(game->GetTexture("Assets/laser.png"));

	//inputcomponent Ãß°¡
	auto* move = new MoveComponent(this);
	move->SetForwardSpeed(800.f);

	mCircle->SetRadius(11.f);
}

Laser::~Laser()
{
	delete mCircle;
}
void Laser::UpdateActor(float deltaTime)
{
	mDeathTimer -= deltaTime;
	if (mDeathTimer < 0.f)
		this->SetState(EDead);

	for(auto* ast:GetGame()->GetAsteroid())
	{
		if(Intersect(*mCircle, (*ast->GetCircle())))
		{
			SetState(EDead);
			ast->SetState(EDead);
			break;
		}
	}

	Vector2 pos = this->GetPosition();
	if (pos.x<10.f || pos.x>1260.f || pos.y<10.f || pos.y>710.f)
	{
		this->SetState(EDead);
	}
}
