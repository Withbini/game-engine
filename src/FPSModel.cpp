#include "FPSModel.hpp"
#include "Game.hpp"
#include "MeshComponent.hpp"

FPSModel::FPSModel(Game* game)
	:Actor(game)
	,mVisible(false)
{
	mMeshComp = new MeshComponent(this);
}

void FPSModel::Load(const std::string& modelFile)
{
	mMeshComp->SetMesh(this->GetGame()->GetRenderer()->GetMesh(modelFile));
}

void FPSModel::SetVisible(bool visible)
{
	mVisible = visible;
}
