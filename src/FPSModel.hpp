#pragma once
#include "Actor.hpp"

class FPSModel :
	public Actor
{
public:
	FPSModel(class Game* game);
	~FPSModel() override = default;

	void Load(const std::string& s);
	void SetVisible(bool);
	bool GetVisible() const { return mVisible;}
private:
	class MeshComponent* mMeshComp;
	bool mVisible;
};

