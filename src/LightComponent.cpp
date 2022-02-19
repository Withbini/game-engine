#include "LightComponent.hpp"
#include "Game.hpp"
#include "Actor.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "VertexArray.hpp"
LightComponent::LightComponent(Actor* owner)
	:Component(owner)
{
	owner->GetGame()->GetRenderer()->AddPointLight(this);
}

LightComponent::~LightComponent()
{
	
	mOwner->GetGame()->GetRenderer()->RemovePointLight(this);
}

void LightComponent::Draw(Shader* shader, Mesh* mesh) const
{
	Matrix4 scale = Matrix4::CreateScale(mOwner->GetScale()*mOuterRadius / mesh->GetRadius());
	Matrix4 trans = Matrix4::CreateTranslation(mOwner->GetPosition());
	shader->SetMat4("world", scale*trans);
	shader->setVec3("light.position", mOwner->GetPosition());
	shader->setVec3("light.diffuseColor", mDiffuseColor);
	shader->SetFloat("light.inRadius", mInnerRadius);
	shader->SetFloat("light.outRadius", mOuterRadius);

	glDrawElements(GL_TRIANGLES, mesh->GetVertexArray()->GetNumIndices(), GL_UNSIGNED_INT, nullptr);
}