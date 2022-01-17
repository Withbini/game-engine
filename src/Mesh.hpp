#pragma once
#include <string>
#include <vector>

class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(const std::string& file, class Game* game);
	void UnLoad();
	class VertexArray* GetVertexArray() const { return mVertexArray; }
	const std::string& GetShader() const { return mShaderName; }
	float GetRadius() const { return mRadius; }
private:
	class VertexArray *mVertexArray;
	std::string mShaderName;
	float mRadius;
	std::vector<class Texture*> mTextures;
};