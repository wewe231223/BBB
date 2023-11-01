#pragma once

enum class Qualifier {
	POSITION,
	ROTATION,
	SCALE,
	PARENT
};

enum class Animation_Input {
	Rotate
};



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


	

	std::shared_ptr<Model> m_parent{nullptr};

public:


	void Render(UINT sid);
	void Update(float dt);

	template<typename T,typename Q>
	void Set(T Src,Q Qualify) {};

	template<>
	void Set(const glm::vec3 Src, Qualifier Qualify) { if (Qualify == Qualifier::POSITION) { m_position = Src; } else { m_rotation = Src; } };

	template<>
	void Set(float3 Src, Qualifier Qualify) { m_scale = Src; }

	template<>
	void Set(std::shared_ptr<Model> Src, Qualifier Qualify) { m_parent = Src; }





	glm::mat4 GetMatrix() { return m_transform; }
	std::shared_ptr<Model> GetParent() { return m_parent; }

};
	