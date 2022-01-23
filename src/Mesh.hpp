#pragma once
#include <string>
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& file, class Renderer* renderer);
	void UnLoad();
	class VertexArray* GetVertexArray() const { return mVertexArray; }
	const std::string& GetShader() const { return mShaderName; }
	class Texture* GetTexture(size_t index);
	float GetRadius() const { return mRadius; }
	float GetSpecPower() const {return mSpecPower;}
private:
	std::string read(const std::string& path);

	class VertexArray *mVertexArray;
	std::string mShaderName;
	float mRadius;
	std::vector<class Texture*> mTextures;

	float mSpecPower;
};