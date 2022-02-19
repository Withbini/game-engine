#pragma once
#include "Common.hpp"
#include "Texture.hpp"

CLASS_PTR(Material)
class Material
{
public:
	static MaterialUPtr Create()
	{
		return MaterialUPtr(new Material);
	}
	TexturePtr diffuse;
	TexturePtr specular;
	float shineness {32.f};

	void Bind(const class Shader*) const;
private:
	Material() = default;
};

CLASS_PTR(Mesh)
class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Create(const std::string& file, class Renderer* renderer);
	void Draw(const class Shader*) const;
	void UnLoad();
	void CreateBox();
	void SetMaterial(MaterialPtr material) { mMaterial = material; }
	MaterialPtr GetMaterial() const { return mMaterial; }
	
	class VertexArray* GetVertexArray() const { return mVertexArray; }
	void SetVertexArray(class VertexArray* vertex);
	const std::string& GetShader() const { return mShaderName; }
	TexturePtr GetTexture(size_t index);
	float GetRadius() const { return mRadius; }
	float GetSpecPower() const {return mSpecPower;}
private:
	std::string read(const std::string& path);

	class VertexArray *mVertexArray;
	std::string mShaderName;
	float mRadius;
	std::vector<TexturePtr> mTextures;
	float mSpecPower;

	MaterialPtr mMaterial;

	friend class MeshComponent;
};
