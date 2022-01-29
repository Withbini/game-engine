#include "CameraComponent.hpp"
#include "Game.hpp"

CameraComponent::CameraComponent(Actor* owner, int order)
	:Component(owner, order)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::SetViewMatrix(const Matrix4& view)
{
	Game* game = mOwner->GetGame();
	game->GetRenderer()->SetViewMatrix(view);
}
