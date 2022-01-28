#include "CameraComponent.hpp"
#include "Game.hpp"

CameraComponent::CameraComponent(Actor* owner, int order)
	:Component(owner, order)
	,mVisible(false)
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::SetVisible(bool visible)
{
	mVisible = visible;
}

void CameraComponent::SetViewMatrix(const Matrix4& view)
{
	if (mVisible) {
		Game* game = mOwner->GetGame();
		game->GetRenderer()->SetViewMatrix(view);
	}
}
