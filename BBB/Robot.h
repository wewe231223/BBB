#pragma once
#include "Mesh.h"
#include "Model.h"

#include "Rigidbody_.h"
#include "Collide_Functions.h"

#include <numeric>


constexpr bool Idle = false;
constexpr bool Walk = true;


class Robot final : public Rigidbody {

public:
	Robot(UINT sid, std::shared_ptr<Mesh> mesh);

private:
	// final model 
	std::shared_ptr<Model> m_body{ nullptr };
	std::unique_ptr<Model> m_head{ nullptr };
	std::unique_ptr<Model> m_rightHand{ nullptr };
	std::unique_ptr<Model> m_leftHand{ nullptr };
	std::unique_ptr<Model> m_rightLeg{ nullptr };
	std::unique_ptr<Model> m_leftLeg{ nullptr };




	bool m_status = Idle;





	float3 m_bounding_Box_Left_Bottom{};
	float3 m_bounding_Box_Right_Top{};





	float m_swingSpeed = 100.f;
	float m_movingSpeed = 2.f;

	float m_gravity = 9.8f;
	float m_Y_Force{};
	glm::vec3 m_moveForce{ };





	//void Jump() { m_moveForce.y = jumpPower; }
	//void Gravity(float deltaTime) { m_moveForce.y -= m_gravity * deltaTime; }
	//void Move(float deltaTime) { m_position += m_moveForce * deltaTime; }



	bool m_jumpFlag = false;
	float m_jumpdt{};
	float mass = 10.f;


private:

	void Handle_Input(glm::vec3& Movement,float dt);
	void Handle_Gravity(glm::vec3& Movement, float dt);



	void Add_Force(float Force);

	float temp = 1.f;


public:

	virtual void Update(float dt) override;
	virtual void Render(UINT sid) override;

	virtual std::tuple<float3, float3> Get_Bounding_Box() { return std::make_tuple(m_bounding_Box_Left_Bottom, m_bounding_Box_Right_Top); };

	
};

