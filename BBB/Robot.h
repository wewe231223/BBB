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




	float m_swingSpeed = 100.f;
	float m_movingSpeed = 2.f;




private:

	void Handle_Input(glm::vec3& Movement,float dt);
	void Handle_Gravity(glm::vec3& Movement, float dt);




	float temp = 1.f;


public:

	virtual void Update(float dt) override;
	virtual void Render(UINT sid) override;


	
};

