#pragma once


typedef std::tuple<glm::vec3, glm::vec3, glm::vec3, float, float, float>  OBB_PARAMETER;
bool OBB(glm::vec3 rigid1_Position, glm::vec3 rigid2_Position, OBB_PARAMETER rigid1, OBB_PARAMETER rigid2);
bool SeparatePlaneExistance(glm::vec3 Posvec, glm::vec3 Plane, std::tuple<glm::vec3, glm::vec3, glm::vec3, float, float, float > Box1,
	std::tuple<glm::vec3, glm::vec3, glm::vec3, float, float, float> Box2);




class Rigidbody{
protected:
	


	glm::vec3 m_axisX{ 1.f,0.f,0.f };
	glm::vec3 m_axisY{ 0.f,1.f,0.f };
	glm::vec3 m_axisZ{ 0.f,0.f,1.f };

	float m_volumeX{1.f};
	float m_volumeY{1.f};
	float m_volumeZ{1.f};



protected:
	std::vector<std::shared_ptr<Rigidbody>> m_collides{};


	glm::vec3 m_deltaPosition{};
	glm::vec3 m_position{};
	glm::vec3 m_scale{};

	glm::vec3 m_bodyRotateAngle{ };


	float m_mass{};



	glm::vec3 m_velocity{};
	glm::vec3 m_force{};
	glm::vec3 m_rotate{};





public:

	Rigidbody() = default;
	Rigidbody(glm::vec3 position, float mass) : m_position(position), m_mass(mass) {};


	void Rotate(glm::vec3 rotation);
	void Movement(glm::vec3 movement);

	void AddCollide(std::shared_ptr<Rigidbody> other) { m_collides.push_back(other); }


	std::tuple<glm::vec3, glm::vec3, glm::vec3, float, float, float> MakeOBBParameter() { return std::make_tuple(m_axisX,m_axisY,m_axisZ,m_volumeX,m_volumeY,m_volumeZ); }



	virtual void Update(float dt);
	virtual void Render(UINT sid) = 0;

	const glm::vec3 GetPosition() { return m_position; };
	




};

