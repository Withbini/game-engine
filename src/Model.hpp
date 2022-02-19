#pragma once
#include "Common.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"

CLASS_PTR(Model);
class Model {
public:
	static ModelUPtr Load(const std::string& filename);

	size_t GetMeshCount() const { return mMeshes.size(); }
	class Mesh* GetMesh(int index) const { return mMeshes[index].get(); }
	void Draw(const class Shader*) const;

private:
	Model() {}
	bool LoadByAssimp(const std::string& filename);
	void ProcessMesh(aiMesh* mesh, const aiScene* scene);
	void ProcessNode(aiNode* node, const aiScene* scene);

	std::vector<MeshUPtr> mMeshes;
	std::vector<MaterialPtr> mMaterials;
};