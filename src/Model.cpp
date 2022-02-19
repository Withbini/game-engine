#include "Model.hpp"
#include "Format.hpp"
#include "Image.hpp"
#include "Mesh.hpp"
#include "VertexArray.hpp"

ModelUPtr Model::Load(const std::string& filename)
{
	auto model = ModelUPtr(new Model);
	if (model->LoadByAssimp(filename))
	{
		return std::move(model);
	}
	return nullptr;
}

void Model::Draw(const Shader* shader) const
{
	for (auto& mesh : mMeshes)
	{
		mesh->Draw(shader);
	}
}

bool Model::LoadByAssimp(const std::string& filename) {
	Assimp::Importer importer;
	const auto scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		SDL_Log("failed to load model: %s", filename);
		return false;
	}

	auto dirname = filename.substr(0, filename.find_last_of("/"));
	auto LoadTexture = [&](aiMaterial* material, aiTextureType type) -> TexturePtr {
		if (material->GetTextureCount(type) <= 0)
			return nullptr;
		aiString filepath;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &filepath);
		auto image = Image::Load(Format::string_format("%s/%s", dirname.c_str(), filepath.C_Str()));
		if (!image)
			return nullptr;
		return Texture::CreateFromImage(image.get());
	};

	for (uint32_t i = 0; i < scene->mNumMaterials; i++) {
		auto material = scene->mMaterials[i];
		auto glMaterial = Material::Create();
		glMaterial->diffuse = LoadTexture(material, aiTextureType_DIFFUSE);
		glMaterial->diffuse->SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		glMaterial->specular = LoadTexture(material, aiTextureType_SPECULAR);
		glMaterial->specular->SetWrap(GL_CLAMP_TO_EDGE, GL_CLAMP_TO_EDGE);
		mMaterials.push_back(std::move(glMaterial));
	}

	ProcessNode(scene->mRootNode, scene);
	return true;
}

void Model::ProcessMesh(aiMesh* mesh, const aiScene* scene) {
	SDL_Log("process mesh name: %s, #vert: %d, #face: %d",
		mesh->mName.C_Str(), mesh->mNumVertices, mesh->mNumFaces);

	std::vector<Vertex> vertices;
	vertices.resize(mesh->mNumVertices);
	for (uint32_t i = 0; i < mesh->mNumVertices; i++) {
		auto& v = vertices[i];
		v.position = glm::vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		v.normal = glm::vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);
		v.texCoord = glm::vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
	}

	std::vector<uint32_t> indices;
	indices.resize(mesh->mNumFaces * 3);
	for (uint32_t i = 0; i < mesh->mNumFaces; i++) {
		indices[3 * i] = mesh->mFaces[i].mIndices[0];
		indices[3 * i + 1] = mesh->mFaces[i].mIndices[1];
		indices[3 * i + 2] = mesh->mFaces[i].mIndices[2];
	}

	auto* vertexArray = new VertexArray(vertices, indices);
	auto nMesh = MeshUPtr(new Mesh);
	nMesh->SetVertexArray(vertexArray);

	if (mesh->mMaterialIndex >= 0)
		nMesh->SetMaterial(mMaterials[mesh->mMaterialIndex]);
	mMeshes.push_back(std::move(nMesh));
}

void Model::ProcessNode(aiNode* node, const aiScene* scene) {
	for (uint32_t i = 0; i < node->mNumMeshes; i++) {
		auto meshIndex = node->mMeshes[i];
		auto mesh = scene->mMeshes[meshIndex];
		ProcessMesh(mesh, scene);
	}

	for (uint32_t i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}
