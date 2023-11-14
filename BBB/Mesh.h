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
	unsigned int m_vbo{};




public:
	const UINT  GetMesh() { return m_vao; }
	const size_t  GetVertexCount(){ return m_vertexCount; }
};


void RenderCube(UINT sid,float3 Left_Bottom, float3 Right_Top);
void RenderCube(UINT sid, glm::vec3 Left_Bottom, glm::vec3 Right_Top);
void RenderVector(UINT sid, glm::vec3 Startpoint, glm::vec3 Vector);
