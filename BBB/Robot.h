#pragma once
#include "Mesh.h"
#include "Model.h"

#include "Collide_Functions.h"

#include <numeric>


constexpr bool Idle = false;
constexpr bool Walk = true;


class Robot final: public MonoObject{

public:
	Robot(UINT sid, std::shared_ptr<Mesh> mesh);

private:
	std::shared_ptr<Model> m_body{nullptr};





	// final model 
	std::unique_ptr<Model> m_head{ nullptr };


	//
	std::unique_ptr<Model> m_rightHand{ nullptr };
	std::unique_ptr<Model> m_leftHand{ nullptr };

	std::unique_ptr<Model> m_rightLeg{ nullptr };
	std::unique_ptr<Model> m_leftLeg{ nullptr };

	bool m_status = Idle;


	glm::vec3 m_position{ 0.f,10.f,0.f };


	float3 m_bounding_Box_Left_Bottom{};
	float3 m_bounding_Box_Right_Top{};



	
	
	float m_swingSpeed = 100.f;
	float m_movingSpeed = 2.f;

	float m_gravity = 9.8f;
	float m_Y_Force{};
	float m_jumpDeltaTime{};

private:

	void HandleInput(glm::vec3& Movement,float dt);


public:

	virtual void Update(float dt);
	virtual void Render(UINT sid);

	virtual std::tuple<float3, float3> Get_Bounding_Box() { return std::make_tuple(m_bounding_Box_Left_Bottom, m_bounding_Box_Right_Top); };

	virtual void Add_Collide(std::shared_ptr<MonoObject> otherObject) { m_Collides.push_back(otherObject); }
	
};

