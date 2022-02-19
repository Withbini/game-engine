#pragma once
#include "Common.hpp"

class VertexArray
{
public:
	VertexArray(const void* verts, unsigned int numVerts, const unsigned int* indices, unsigned int numIndices);
	VertexArray(const std::vector<Vertex>& verts, const std::vector<uint32_t>& indices);
	~VertexArray();

	void Bind() const;

	unsigned int GetNumIndices() const { return mNumIndices; }
	unsigned int GetNumVerts() const { return mNumVerts; }
private:
	unsigned int mNumVerts {0};
	unsigned int mNumIndices {0};
	unsigned int mVertexBuffer {0};
	unsigned int mIndexBuffer {0};
	unsigned int mVertexArray {0};
};
