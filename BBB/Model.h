#pragma once

enum class Qualifier {
	POSITION,
	PIVOT,
	ROTATION,
	SCALE,
	PARENT,


	MAX_ROTATION,
	MIN_ROTATION
};

enum class Animation_Input {
	Rotate
};

class Object abstract{
public:
	virtual void Render(UINT sid) = 0;
	virtual void Update(float dt) = 0;
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


	glm::mat4 m_WorldMatrix{ 1.f };
	
	
	glm::mat4 m_transMatrix{ 1.f };
	glm::mat4 m_rotationMatrix{ 1.f };
	glm::mat4 m_scaleMatrix{ 1.f };



	glm::vec3 m_position{0.f};

	glm::vec3 m_pivot{ 0.f };
	glm::vec3 m_max_Rotation{ 360.f,360.f,360.f };
	glm::vec3 m_min_Rotation{ -360.f,-360.f,-360.f };
	glm::vec3 m_rotation{0.f};

	glm::vec3 m_scale{1.f,1.f,1.f};

	glm::vec3 m_rotateDir{ 0.f,0.f,0.f };
	

	std::shared_ptr<Model> m_parent{nullptr};


	GLenum m_renderMode = GL_FILL;


public:


	void Render(UINT sid);
	void Update(float dt);

	template<typename T,typename Q>
	void Set(T Src,Q Qualify) {};

	template<>
	void Set(const glm::vec3 Src, Qualifier Qualify);

	template<>
	void Set(float Src, Qualifier Quailfy) {}

	template<>
	void Set(std::shared_ptr<Model> Src, Qualifier Qualify) { m_parent = Src; }


	


	glm::mat4 GetTransMat() { return m_transMatrix; }
	glm::mat4 GetRotMat() { return m_rotationMatrix; }
	glm::mat4 GetScaleMat() { return m_scaleMatrix;  }


	glm::mat4 GetWorldMat() { return m_WorldMatrix; }
	
	
	
	glm::vec3 GetScale() { return m_scale; }
	glm::vec3 GetPosition() { return m_position;  }

	std::shared_ptr<Model> GetParent() { return m_parent; }


	void Rotate(glm::vec3 dir) { m_rotateDir = dir; }
	void DelRotate() { m_rotateDir = glm::vec3{ 0.f }; }


	
	void LinearMove(glm::vec3 P1,glm::vec3 P2,float t);
	void ScalarMove(glm::vec3 Movement) { m_position += Movement; };

	void Shrink() { m_scale.x -= 1.f; }
};

