#include "3dGame.hpp"

#include "FollowActor.hpp"
#include "FPSActor.hpp"
#include "MeshComponent.hpp"
#include "OrbitActor.hpp"
#include "PlaneActor.hpp"
#include "SplineActor.hpp"
#include "SpriteComponent.hpp"

void GL3DGame::LoadData()
{
	// Create actors
	Actor* a = new Actor(this);
	a->SetPosition(Vector3(200.0f, 75.0f, 0.0f));
	a->SetScale(100.0f);
	Quaternion q(Vector3::UnitY, -Math::PiOver2);
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi + Math::Pi / 4.0f));
	a->SetRotation(q);
	MeshComponent* mc = new MeshComponent(a);
	mc->SetMesh(mRenderer->GetMesh("Assets/Cube.gpmesh"));

	a = new Actor(this);
	a->SetPosition(Vector3(200.0f, -75.0f, 0.0f));
	a->SetScale(3.0f);
	mc = new MeshComponent(a);
	mc->SetMesh(mRenderer->GetMesh("Assets/Sphere.gpmesh"));

	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			a = new PlaneActor(this);
			a->SetPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::UnitX, Math::PiOver2);
	for (int i = 0; i < 10; i++)
	{
		a = new PlaneActor(this);
		a->SetPosition(Vector3(start + i * size, start - size, 0.0f));
		a->SetRotation(q);

		a = new PlaneActor(this);
		a->SetPosition(Vector3(start + i * size, -start + size, 0.0f));
		a->SetRotation(q);
	}

	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::PiOver2));
	// Forward/back walls
	for (auto i = 0; i < 10; i++)
	{
		a = new PlaneActor(this);
		a->SetPosition(Vector3(start - size, start + i * size, 0.0f));
		a->SetRotation(q);

		a = new PlaneActor(this);
		a->SetPosition(Vector3(-start + size, start + i * size, 0.0f));
		a->SetRotation(q);
	}

	mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	DirectionalLight& dir = mRenderer->GetDirectionalLight();
	dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

	// Camera actor
	mFPSActor = new FPSActor(this);
	mFollowActor = new FollowActor(this);
	mSplineActor = new SplineActor(this);
	mOrbitActor = new OrbitActor(this);

	// UI elements
	a = new Actor(this);
	a->SetPosition(Vector3(-350.0f, -250.0f, 0.0f));
	SpriteComponent* sc = new SpriteComponent(a);
	sc->SetTexture(mRenderer->GetTexture("Assets/HealthBar.png"));

	a = new Actor(this);
	a->SetPosition(Vector3(375.0f, -255.0f, 0.0f));
	a->SetScale(0.75f);
	sc = new SpriteComponent(a);
	sc->SetTexture(mRenderer->GetTexture("Assets/Radar.png"));

	ChangeCamera(1);

	MouseMode(true);
}

void GL3DGame::HandleKeyPress(SDL_KeyboardEvent* key)
{
	Game::HandleKeyPress(key);
	switch (key->keysym.sym)
	{
		case '1':
		case '2':
		case '3':
		case '4':
			ChangeCamera(key->keysym.sym);
			break;
		default:
			break;
	}
}

void GL3DGame::ChangeCamera(int key)
{
	//by default
	mFPSActor->SetState(Actor::EActive);
	mFPSActor->SetVisible(true);
	mFollowActor->SetState(Actor::EPause);
	mSplineActor->SetState(Actor::EPause);
	mOrbitActor->SetState(Actor::EPause);

	switch (key)
	{
	case '1':
		mFPSActor->SetState(Actor::EActive);
		break;
	case '2':
		mFPSActor->SetState(Actor::EPause);
		mFollowActor->SetState(Actor::EActive);
		mFPSActor->SetVisible(false);
		break;
	case '3':
		mFPSActor->SetState(Actor::EPause);
		mOrbitActor->SetState(Actor::EActive);
		mFPSActor->SetVisible(false);
		break;
	case '4':
		mFPSActor->SetState(Actor::EPause);
		mSplineActor->SetState(Actor::EActive);
		mSplineActor->ResetSpline();
		mFPSActor->SetVisible(false);
		break;
	default:
		break;
	}
}