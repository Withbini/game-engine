#include "PlaneActor.hpp"
#include "Game.hpp"
#include "MeshComponent.hpp"

PlaneActor::PlaneActor(Game* game) :
	Actor(game)
{
	SetScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->SetMesh(GetGame()->GetRenderer()->GetMesh("Assets/Plane.gpmesh"));
}

PlaneActor::~PlaneActor()
{
}
