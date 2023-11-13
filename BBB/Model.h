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

constexpr auto Positive = 1.f;
constexpr auto Negative = -1.f;





class MonoObject abstract {
protected:
	std::vector<std::shared_ptr<MonoObject>> m_Collides{};


	glm::vec3 m_position{ 0.f,10.f,0.f };
	glm::vec3 m_scale{ 1.f,1.f,1.f };


public:
	MonoObject() = default;

	virtual void Render(UINT sid) = 0;
	virtual void Update(float dt) = 0;

	virtual std::tuple<float3, float3> Get_Bounding_Box() = 0;
	virtual void Add_Collide(std::shared_ptr<MonoObject> otherObject) { m_Collides.push_back(otherObject); }

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
	glm::mat4 m_rotationMatrix{ 0.f };
	glm::mat4 m_scaleMatrix{ 1.f };



	glm::vec3 m_position{0.f};

	glm::vec3 m_pivot{ 0.f };
	
	glm::vec3 m_max_Rotation{ 360.f ,360.f,360.f };
	glm::vec3 m_min_Rotation{ -360.f , -360.f ,  -360.f };
	
	float m_rotate_dir = Positive;


	glm::vec3 m_rotation{0.f};


	glm::vec3 m_scale{1.f,1.f,1.f};

	glm::vec3 m_rotate_speed{ 0.f,0.f,0.f };
	

	std::shared_ptr<Model> m_parent{nullptr};




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


	std::shared_ptr<Model> GetParent() { return m_parent; }


	void Rotate(glm::vec3 speed) {  m_rotate_speed = speed; }
	
	void SetRotateDir(float dir) { m_rotate_dir = dir; }

	void DelRotate() { m_rotate_speed = glm::vec3{ 0.f }; m_rotation = glm::vec3{ 0.f }; }


	void Shrink() { m_scale *= 0.1f; }


	void RotateScalar(glm::vec3 Rotate) { m_rotation = Rotate; }
	void MoveScalar(glm::vec3 Movement) { m_position += Movement; }
	
};

