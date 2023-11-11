#include "pch.h"
#include "Robot.h"
#include "Input.h"


/*
	1010	1000	1001
	0010	0000	0001
	0110	0100	0101



	-45		0		45
	-90		0		90
	-135	180		135
*/



Robot::Robot(UINT sid,std::shared_ptr<Mesh> mesh){
// 	m_mainBody = std::make_shared<Model>(sid, mesh->GetMesh(),mesh->GetVertexCount());


	m_body = std::make_shared<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());

	m_body->Set(glm::vec3{ 10.f,10.f,10.f }, Qualifier::POSITION);
	m_body->Set(glm::vec3{ 5.f,7.f,3.f }, Qualifier::SCALE);


	m_head = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_head->Set(m_body, Qualifier::PARENT);

	m_head->Set(glm::vec3(0.f, 0.5f, 0.f), Qualifier::PIVOT);


	m_head->Set(glm::vec3{ 0.f,0.5f,0.f }, Qualifier::POSITION);
	m_head->Set(glm::vec3( 0.f,0.5f,0.f), Qualifier::PIVOT);
	m_head->Set(glm::vec3{ 2.f,2.f,2.f }, Qualifier::SCALE);

	



	m_rightHand = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_rightHand->Set(m_body, Qualifier::PARENT);

	
	m_leftHand = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_leftHand->Set(m_body, Qualifier::PARENT);

	
	m_rightLeg = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_rightLeg->Set(m_body, Qualifier::PARENT);

	m_leftLeg = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_leftLeg->Set(m_body, Qualifier::PARENT);




	m_rightHand->Set(glm::vec3(0.5f, 0.4f, 0.f), Qualifier::POSITION);
	m_rightHand->Set(glm::vec3(0.f, 0.f, 45.f), Qualifier::MAX_ROTATION);
	m_rightHand->Set(glm::vec3(0.f, 0.f, -45.f), Qualifier::MIN_ROTATION);
	m_rightHand->Set(glm::vec3(0.5f, -0.4f, 0.f), Qualifier::PIVOT);
	m_rightHand->Set(glm::vec3(1.5f, 5.f, 1.5f), Qualifier::SCALE);
	




	m_leftHand->Set(glm::vec3(-0.5f, 0.4f, 0.f), Qualifier::POSITION);
	m_leftHand->Set(glm::vec3(0.f, 0.f, 45.f), Qualifier::MAX_ROTATION);
	m_leftHand->Set(glm::vec3(0.f, 0.f, -45.f), Qualifier::MIN_ROTATION);
	m_leftHand->Set(glm::vec3(-0.5f, -0.4f, 0.f), Qualifier::PIVOT);
	m_leftHand->Set(glm::vec3(1.5f, 5.f, 1.5f), Qualifier::SCALE);
	m_leftHand->SetRotateDir(Negative);




	m_rightLeg->Set(glm::vec3(0.3f, -0.45f, 0.f), Qualifier::POSITION);
	m_rightLeg->Set(glm::vec3(0.f, 0.f, 45.f), Qualifier::MAX_ROTATION);
	m_rightLeg->Set(glm::vec3(0.f, 0.f, -45.f), Qualifier::MIN_ROTATION);
	m_rightLeg->Set(glm::vec3(0.f, -0.5f, 0.f), Qualifier::PIVOT);
	m_rightLeg->Set(glm::vec3(1.5f, 5.f, 1.5f), Qualifier::SCALE);



	m_leftLeg->Set(glm::vec3(-0.3f, -0.45f, 0.f), Qualifier::POSITION);
	m_leftLeg->Set(glm::vec3(0.f, 0.f, 45.f), Qualifier::MAX_ROTATION);
	m_leftLeg->Set(glm::vec3(0.f, 0.f, -45.f), Qualifier::MIN_ROTATION);
	m_leftLeg->Set(glm::vec3(0.f, -0.5f, 0.f), Qualifier::PIVOT);
	m_leftLeg->Set(glm::vec3(1.5f, 5.f, 1.5f), Qualifier::SCALE);
	m_leftLeg->SetRotateDir(Negative);
	



	m_body->Shrink();



	
}

void Robot::HandleInput(glm::vec3& Movement,float dt)
{

	KEY_STATE Up = Input::GetInstance()->GetKey(GLFW_KEY_UP);
	KEY_STATE Down = Input::GetInstance()->GetKey(GLFW_KEY_DOWN);
	KEY_STATE Right = Input::GetInstance()->GetKey(GLFW_KEY_RIGHT);
	KEY_STATE Left = Input::GetInstance()->GetKey(GLFW_KEY_LEFT);



	if (Up == KEY_STATE::PRESS) {

		m_status = Walk;
		// 0
		Movement.z -= m_movingSpeed * dt;

		m_body->RotateScalar(glm::vec3{ 0.f,0.f,0.f });



	}
	else if (Up == KEY_STATE::RELEASE) {
		m_status = Idle;
	}


	if (Down == KEY_STATE::PRESS) {

		m_status = Walk;
		// 180
		Movement.z += m_movingSpeed * dt;
		m_body->RotateScalar(glm::vec3{ 0.f,180.f,0.f });


	}
	else if (Down == KEY_STATE::RELEASE) {

		m_status = Idle;
	}







	if (Right == KEY_STATE::PRESS) {
		m_status = Walk;
		// -90

		Movement.x += m_movingSpeed * dt;


		if (Up == KEY_STATE::PRESS) {
			m_body->RotateScalar(glm::vec3{ 0.f,-45.f,0.f });
		}
		else if (Down == KEY_STATE::PRESS) {
			m_body->RotateScalar(glm::vec3{ 0.f,-135.f,0.f });
		}
		else {
			m_body->RotateScalar(glm::vec3{ 0.f,-90.f,0.f });
		}





	}
	else if (Right == KEY_STATE::RELEASE) {
		m_status = Idle;
	}

	if (Left == KEY_STATE::PRESS) {
		m_status = Walk;

		// 90
		Movement.x -= m_movingSpeed * dt;


		if (Up == KEY_STATE::PRESS) {
			m_body->RotateScalar(glm::vec3{ 0.f,45.f,0.f });

		}
		else if (Down == KEY_STATE::PRESS) {
			m_body->RotateScalar(glm::vec3{ 0.f,135.f,0.f });
		}
		else {
			m_body->RotateScalar(glm::vec3{ 0.f,90.f,0.f });
		}

	}
	else if (Left == KEY_STATE::RELEASE) {
		m_status = Idle;
	}




	if (Input::GetInstance()->GetKey(GLFW_KEY_EQUAL) == KEY_STATE::DOWN) {
		m_swingSpeed += 20.f;
		m_movingSpeed += 0.5f;
	}


	if (Input::GetInstance()->GetKey(GLFW_KEY_MINUS) == KEY_STATE::DOWN) {
		m_swingSpeed -= 20.f;
		m_movingSpeed -= 0.5f;
	}

	m_swingSpeed = std::clamp(m_swingSpeed, 0.f, 1000.f);
	m_movingSpeed = std::clamp(m_movingSpeed, 0.f, 1000.f);


	if (Input::GetInstance()->GetKey(GLFW_KEY_EQUAL) == KEY_STATE::DOWN) {
	}


	if (m_status == Walk) {
		m_rightHand->Rotate(glm::vec3(0.f, 0.f, m_swingSpeed));
		m_leftHand->Rotate(glm::vec3(0.f, 0.f, m_swingSpeed));

		m_rightLeg->Rotate(glm::vec3(0.f, 0.f, m_swingSpeed));
		m_leftLeg->Rotate(glm::vec3(0.f, 0.f, m_swingSpeed));

	}
	else {

		m_rightHand->DelRotate();
		m_leftHand->DelRotate();

		m_rightLeg->DelRotate();
		m_leftLeg->DelRotate();

	}

}

void Robot::Update(float dt){


	if (Input::GetInstance()->GetKey(GLFW_KEY_SPACE) == KEY_STATE::DOWN) {
		m_Y_Force += 1.f;

	}

	glm::vec3 Movement{};


	HandleInput(Movement, dt);


	if (Input::GetInstance()->GetKey(GLFW_KEY_EQUAL) == KEY_STATE::DOWN) {
		m_swingSpeed += 20.f;
		m_movingSpeed += 0.5f;
	}


	if (Input::GetInstance()->GetKey(GLFW_KEY_MINUS) == KEY_STATE::DOWN) {
		m_swingSpeed -= 20.f;
		m_movingSpeed -= 0.5f;
	}

	m_swingSpeed = std::clamp(m_swingSpeed, 0.f, 1000.f );
	m_movingSpeed = std::clamp(m_movingSpeed, 0.f, 1000.f);


	if (Input::GetInstance()->GetKey(GLFW_KEY_EQUAL) == KEY_STATE::DOWN) {
	}


	if (m_status == Walk) {
		m_rightHand->Rotate(glm::vec3(0.f, 0.f, m_swingSpeed));
		m_leftHand->Rotate(glm::vec3(0.f, 0.f, m_swingSpeed));

		m_rightLeg->Rotate(glm::vec3(0.f, 0.f, m_swingSpeed));
		m_leftLeg->Rotate(glm::vec3(0.f, 0.f, m_swingSpeed));

	}
	else {

		m_rightHand->DelRotate();
		m_leftHand->DelRotate();

		m_rightLeg->DelRotate();
		m_leftLeg->DelRotate();

	}

	Movement.y += m_Y_Force;
	m_Y_Force -= 0.098f;
	Movement.y -= m_gravity * dt;
	m_Y_Force = std::clamp(m_Y_Force, 0.f, FLT_MAX);
	m_position.y = std::clamp(m_position.y, 0.8f, FLT_MAX);

	m_position += Movement;

	m_body->Set(m_position, Qualifier::POSITION);

	m_bounding_Box_Left_Bottom = float3{ m_position.x - 0.4f,m_position.y - 0.8f,m_position.z - 0.2f };
	m_bounding_Box_Right_Top = float3{ m_position.x + 0.4f,m_position.y + 0.6f,m_position.z + 0.2f };


	bool CollideFlag = false;


	for (auto& o : m_Collides) {

		std::tuple<float3, float3> o_bb{ o->Get_Bounding_Box() };

		float3 o_bb_Left_bottom{ std::get<0>(o_bb) };
		float3 o_bb_Right_Top{ std::get<1>(o_bb) };

		if (AABB(m_bounding_Box_Left_Bottom, m_bounding_Box_Right_Top, o_bb_Left_bottom, o_bb_Right_Top)) {
			CollideFlag = true;
		}


		if (m_bounding_Box_Left_Bottom.y + 0.01f > o_bb_Right_Top.y and CollideFlag) {
			
			Movement.y = 0.f;
			m_gravity = 0.f;
			CollideFlag = false;

		}
		else {
			m_gravity = 9.8f;
		}

	}
	
	std::cout << CollideFlag << std::endl;

	if (CollideFlag) {
		m_position -= Movement;
		m_body->Set(m_position, Qualifier::POSITION);
		m_bounding_Box_Left_Bottom = float3{ m_position.x - 0.4f,m_position.y - 0.8f,m_position.z - 0.2f };
		m_bounding_Box_Right_Top = float3{ m_position.x + 0.4f,m_position.y + 0.6f,m_position.z + 0.2f };
	}




	


	m_body->Update(dt);

	m_rightHand->Update(dt);
	m_leftHand->Update(dt);

	m_rightLeg->Update(dt);
	m_leftLeg->Update(dt);

}



void Robot::Render(UINT sid)
{

	


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	m_body->Render(sid);
	m_head->Render(sid);

	m_rightHand->Render(sid);
	m_leftHand->Render(sid);

	m_rightLeg->Render(sid);
	m_leftLeg->Render(sid);

	RenderCube(sid, m_bounding_Box_Left_Bottom, m_bounding_Box_Right_Top);


}
