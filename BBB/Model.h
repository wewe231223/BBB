#pragma once
class Model {
public:
	Model() = default;
	Model(UINT sid,UINT Vao, size_t VertexCount);
	~Model() = default;

	Model(const Model& other) = default;

	Model& operator=(const Model& other);





private:
	
	UINT m_vao{};
	size_t m_vertexCount{};

	UINT m_transformLocation{ 0 };

	glm::mat4 m_transform{ 0.f };

	glm::vec3 m_position{0.f};
	glm::vec3 m_rotation{0.f};
	float3 m_scale{1.f,1.f,1.f};

	Model* m_Parent{nullptr};

public:


	void Render(UINT sid);
	void Update(float dt);

};
	