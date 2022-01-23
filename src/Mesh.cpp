#include "Mesh.hpp"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>

#include "Renderer.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

using std::string;
using std::vector;

using namespace rapidjson;
Mesh::Mesh()
	: mShaderName("")
	, mVertexArray(nullptr)
	, mRadius(0)
{
}

Mesh::~Mesh()
{
}

string Mesh::read(const string& path)
{
	std::ifstream file(path);
	std::stringstream ss;
	if(file.fail())
	{
		SDL_Log("File %s is not valid", path.c_str());
		file.close();
		assert(false);
		return "";
	}
	ss << file.rdbuf();
	string res = ss.str();

	SDL_Log("File read result: %s", res.c_str());
	file.close();
	return res;
}

bool Mesh::Load(const std::string& file, Renderer* renderer)
{
	Document document;
	string jsonFile = read(file);
	document.Parse(jsonFile.c_str());

	if (!document.IsObject())
	{
		SDL_Log("Mesh %s is not valid", file.c_str());
		return false;
	}

	assert(document["shader"].IsString());
	mShaderName = document["shader"].GetString();

	assert(document["textures"].IsArray());
	const Value& textures = document["textures"];
	std::vector<Texture*> texs;
	for (SizeType i = 0; i < textures.Size(); ++i)
	{
		const string & textureName = textures[i].GetString();
		auto *t = renderer->GetTexture(textureName);
		if (t == nullptr)
		{
			t = renderer->GetTexture("Assets/Default.png");
		}
		mTextures.emplace_back(t);
	}

	mSpecPower = static_cast<float>(document["specularPower"].GetDouble());

	vector<float>vertex;
	Value& vert = document["vertices"];
	vertex.reserve(vert.Size() * 8);
	mRadius = 0.f;
	for (SizeType i = 0; i < vert.Size(); ++i)
	{
		const Value& v = vert[i];
		Vector3 pos(v[0].GetFloat(), v[1].GetFloat(), v[2].GetFloat());
		mRadius = Math::Max(mRadius, pos.LengthSq());
		for (auto j = 0; j < 8; ++j) //TODO: vertex property can be changed.
		{
			vertex.emplace_back(static_cast<float>(vert[i][j].GetDouble()));
		}
	}
	mRadius = Math::Sqrt(mRadius);

	vector<unsigned int> indices;
	Value& index = document["indices"];
	indices.reserve(index.Size() * 3);
	for (SizeType i = 0; i < index.Size(); ++i)
	{
		for (auto j = 0; j < 3; ++j)
		{
			indices.emplace_back(index[i][j].GetUint());
		}
	}
	mVertexArray = new VertexArray(vertex.data(), vertex.size() / 8, indices.data(), static_cast<unsigned>(indices.size()));
	return true;
}

void Mesh::UnLoad()
{
	delete mVertexArray;
	mVertexArray = nullptr;
}

Texture* Mesh::GetTexture(size_t index)
{
	if (index < mTextures.size())
	{
		return mTextures[index];
	}
	return nullptr;
}
