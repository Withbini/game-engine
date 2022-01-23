#include "3dGame.hpp"
#include "CameraActor.hpp"
#include "MeshComponent.hpp"
#include "PlaneActor.hpp"

GL3DGame::GL3DGame()
{
}

GL3DGame::~GL3DGame()
{
}

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
	for (int i = 0; i < 10; i++)
	{
		a = new PlaneActor(this);
		a->SetPosition(Vector3(start - size, start + i * size, 0.0f));
		a->SetRotation(q);

		a = new PlaneActor(this);
		a->SetPosition(Vector3(-start + size, start + i * size, 0.0f));
		a->SetRotation(q);
	}

	// Setup lights
	//mRenderer->SetAmbientLight(Vector3(0.2f, 0.2f, 0.2f));
	//DirectionalLight& dir = mRenderer->GetDirectionalLight();
	//dir.mDirection = Vector3(0.0f, -0.707f, -0.707f);
	//dir.mDiffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	//dir.mSpecColor = Vector3(0.8f, 0.8f, 0.8f);

	//// Camera actor
	//mCameraActor = new CameraActor(this);

	//// UI elements
	//a = new Actor(this);
	//a->SetPosition(Vector3(-350.0f, -350.0f, 0.0f));
	//SpriteComponent* sc = new SpriteComponent(a);
	//sc->SetTexture(mRenderer->GetTexture("Assets/HealthBar.png"));

	//a = new Actor(this);
	//a->SetPosition(Vector3(375.0f, -275.0f, 0.0f));
	//a->SetScale(0.75f);
	//sc = new SpriteComponent(a);
	//sc->SetTexture(mRenderer->GetTexture("Assets/Radar.png"));
}

