#pragma once
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Shader.hpp"
using namespace std;
class Model
{
public:
	vector<Texture>textures_loaded;
	vector<Mesh> meshes;
	string directory;
	bool gammaCorrection;
	
	Model(const char *path, bool gamma = false) :gammaCorrection(gamma)
	{
		loadModel(path);
	}
	void draw(Shader &shader);

private:
	//data
	
	void processNode(aiNode* node, const aiScene *scene);
	Mesh processMesh(aiMesh* mesh, const aiScene *scene);
	vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
	void loadModel(const string &path);
	unsigned int TextureFromFile(const char *path, const string &directory, bool gamma=false);
};
