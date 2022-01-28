#include "FPSModel.hpp"
#include "Game.hpp"
#include "MeshComponent.hpp"

FPSModel::FPSModel(Game* game)
	:Actor(game)
{
	mMeshComp = new MeshComponent(this);
}

void FPSModel::Load(const std::string& modelFile)
{
	mMeshComp->SetMesh(this->GetGame()->GetRenderer()->GetMesh(modelFile));
}