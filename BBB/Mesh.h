#pragma once
class Mesh{
public:
	Mesh(std::string path);
private:

	std::vector<vertex> m_vertex{};
	std::vector<unsigned int> m_vertexIndices{};
	std::vector<unsigned int> m_uvIndices{};
	std::vector<unsigned int> m_normalIndices{};



	size_t m_vertexCount{};

	unsigned int m_vao{};
	unsigned int m_ebo{};

public:
	const UINT  GetMesh() { return m_vao; }
	const size_t  GetVertexCount(){ return m_vertexCount; }

};

