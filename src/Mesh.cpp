#include "Mesh.hpp"

#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>


#include "Game.hpp"
#include "VertexArray.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

using std::string;
using std::vector;

using namespace rapidjson;
Mesh::Mesh()
	:mShaderName(nullptr)
	,mVertexArray(nullptr)
	,mRadius(0)
{
}

Mesh::~Mesh()
{
	delete mVertexArray;
}

string read(const string& path)
{
	struct stat sb {};
	string res;

	FILE* input;
	fopen_s(&input, path.c_str(), "r");
	if (input == nullptr)
	{
		assert(false);
	}

	stat(path.c_str(), &sb);
	res.resize(sb.st_size);
	fread(const_cast<char*>(res.data()), sb.st_size, 1, input);
	fclose(input);

	SDL_Log("%s", res);

	return res;
}
bool ParseJson(Document &doc, const std::string& jsonData)
{
	if (doc.Parse(jsonData.c_str()).HasParseError())
	{
		return false;
	}

	return doc.IsObject();
}
std::string JsonDocToString(Document &doc)
{
	StringBuffer buffer;
	Writer<StringBuffer> writer(buffer);
	doc.Accept(writer);
	return buffer.GetString();
}

bool Mesh::Load(const std::string& file, Game* game)
{
	Document document;
	string jsonFile = read(file);
	document.Parse(jsonFile.c_str());

	assert(document["shader"].IsString());
	mShaderName = document["shader"].GetString();

	assert(document["textures"].IsArray());
	Value& textures = document["textures"];
	std::vector<Texture*> texs;
	for (auto i = 0; i < textures.Size(); ++i)
	{
		texs.push_back(game->GetRenderer()->GetTexture(textures[i].GetString()));
	}

	vector<float>vertex;
	vector<unsigned int> indices;
	Value& vert = document["vertices"];
	for (SizeType i = 0; i < vert.Size(); ++i)
	{
		for (auto j = 0; j < 8; ++j)
		{
			vertex.push_back(vert[i][j].GetFloat());
		}
	}

	Value& index = document["indices"];
	for (SizeType i = 0; i < vert.Size(); ++i)
	{
		for (auto j = 0; j < 3; ++j)
		{
			indices.push_back(index[i][j].GetInt());
		}
	}
	mVertexArray = new VertexArray(vertex.data(), vertex.size(), indices.data(), indices.size());

	std::string jsonString = JsonDocToString(document);
	return true;
}

void Mesh::UnLoad()
{
}
