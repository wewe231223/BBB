#pragma once
class Model {
public:
	Model() = default;
	Model(UINT Vao, size_t VertexCount);
	~Model() = default;

	Model(const Model& other);

	Model& operator=(const Model& other);





private:
	
	UINT m_vao{};
	size_t m_vertexCount{};



	glm::mat4 m_transform{ 1.f };

	glm::vec3 m_position{};
	glm::vec3 m_rotation{};
	float3 m_scale{};

	Model* m_Parent{nullptr};

public:


	void Render(float sid);
	void Update(float dt);

};
