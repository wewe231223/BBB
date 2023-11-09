#include "pch.h"
#include "Tank.h"
#include "Input.h"

Tank::Tank(UINT sid, std::shared_ptr<Mesh> mesh){

	m_mainBody = std::make_shared<Model>(sid, mesh->GetMesh(),mesh->GetVertexCount());



	m_firstHand1 = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_firstHand1->Set(m_mainBody, Qualifier::PARENT);


	m_firstHand2 = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_firstHand2->Set(m_mainBody, Qualifier::PARENT);



	m_subBody1 = std::make_shared<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_subBody1->Set(m_mainBody, Qualifier::PARENT);

	m_secondHand1 = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_secondHand1->Set(m_subBody1, Qualifier::PARENT);


	m_secondHand2 = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_secondHand2->Set(m_subBody1, Qualifier::PARENT);






	m_mainBody->Set(glm::vec3(0.f, 10.f, 0.f), Qualifier::POSITION);
	m_mainBody->Set(glm::vec3(0.f, 0.f, 0.f), Qualifier::ROTATION);
	
	m_mainBody->Set(glm::vec3(0.f, 0.5f, 0.f),Qualifier::PIVOT);
	m_mainBody->Set(glm::vec3{ 15.f,5.f,15.f }, Qualifier::SCALE);



	
	m_firstHand1->Set(glm::vec3(0.5f, 0.5f,0.4f), Qualifier::POSITION);
	m_firstHand1->Set(glm::vec3(0.f, 90.f, 0.f), Qualifier::MAX_ROTATION);
	m_firstHand1->Set(glm::vec3(0.f, -90.f, 0.f), Qualifier::MIN_ROTATION);
	m_firstHand1->Set(glm::vec3(0.5f, 0.f, 0.f),Qualifier::PIVOT);
	m_firstHand1->Set(glm::vec3{ 5.f,1.f,1.f }, Qualifier::SCALE);






	m_firstHand2->Set(glm::vec3(0.5f, 0.5f, -0.4f), Qualifier::POSITION);
	m_firstHand2->Set(glm::vec3(0.f, 90.f, 0.f), Qualifier::MAX_ROTATION);
	m_firstHand2->Set(glm::vec3(0.f, -90.f, 0.f), Qualifier::MIN_ROTATION);
	m_firstHand2->Set(glm::vec3(0.5f, 0.f, 0.f), Qualifier::PIVOT);
	m_firstHand2->Set(glm::vec3{ 5.f,1.f,1.f }, Qualifier::SCALE);








	m_subBody1->Set(glm::vec3{ 0.f,1.f,0.f }, Qualifier::POSITION);
	m_subBody1->Set(glm::vec3{ 0.f,0.f,0.f }, Qualifier::ROTATION);
	m_subBody1->Set(glm::vec3{ 10.f,3.f,10.f }, Qualifier::SCALE);
	m_subBody1->Set(glm::vec3(0.f, 0.5f, 0.f), Qualifier::PIVOT);




	m_secondHand1->Set(glm::vec3{ 0.f,1.f,0.4f }, Qualifier::POSITION);
	m_secondHand1->Set(glm::vec3{ 1.f,5.f,1.f }, Qualifier::SCALE);
	m_secondHand1->Set(glm::vec3(0.f, 0.5f, 0.f), Qualifier::PIVOT);
	m_secondHand1->Set(glm::vec3(90.f, 90.f, 0.f), Qualifier::MAX_ROTATION);
	m_secondHand1->Set(glm::vec3(-90.f, -90.f, 0.f), Qualifier::MIN_ROTATION);







	m_secondHand2->Set(glm::vec3{ 0.f,1.f,-0.4f }, Qualifier::POSITION);
	m_secondHand2->Set(glm::vec3{ 1.f,5.f,1.f }, Qualifier::SCALE);
	m_secondHand2->Set(glm::vec3(0.f, 0.5f, 0.f), Qualifier::PIVOT);
	m_secondHand2->Set(glm::vec3(90.f, 90.f, 0.f), Qualifier::MAX_ROTATION);
	m_secondHand2->Set(glm::vec3(-90.f, -90.f, 0.f), Qualifier::MIN_ROTATION);





	m_firsthand1_P1 = m_firstHand1->GetPosition();
	m_firsthand2_P1 = m_firstHand2->GetPosition();

	m_firsthand1_P2 = (m_firsthand1_P1 + m_firsthand2_P1) / 2.f;
	m_firsthand2_P2 = (m_firsthand1_P1 + m_firsthand2_P1) / 2.f;

}

void Tank::Render(UINT sid){

	
	m_mainBody->Render(sid);
	m_firstHand1->Render(sid);
	m_firstHand2->Render(sid);
	m_subBody1->Render(sid);
	m_secondHand1->Render(sid);
	m_secondHand2->Render(sid);


}

void Tank::Update(float dt){
	if (Input::GetInstance()->GetKey(GLFW_KEY_U) == KEY_STATE::DOWN) {
		m_mainBody->Shrink();
	}

	if (Input::GetInstance()->GetKey(GLFW_KEY_SPACE) == KEY_STATE::DOWN) {
		m_firstHand1->DelRotate();
		m_firstHand2->DelRotate();
		m_secondHand1->DelRotate();
		m_secondHand2->DelRotate();
		m_mainBody->DelRotate();
		m_subBody1->DelRotate();



	}

	if (Input::GetInstance()->GetKey(GLFW_KEY_LEFT) == KEY_STATE::PRESS) {
		// component changes 

		if (Input::GetInstance()->GetKey(GLFW_KEY_LEFT_SHIFT) == KEY_STATE::PRESS) {
			m_mainBody->ScalarMove(glm::vec3{ -0.1f,0.f,0.f });
		}
		else {


			m_firstHand1->Rotate(glm::vec3(0.f, 30.f, 0.f));
			m_firstHand2->Rotate(glm::vec3(0.f, -30.f, 0.f));


			m_secondHand1->Rotate(glm::vec3{ 30.f,0.f,0.f });
			m_secondHand2->Rotate(glm::vec3{ -30.f,0.f,0.f });
		}

	}

	if (Input::GetInstance()->GetKey(GLFW_KEY_RIGHT) == KEY_STATE::PRESS) {
		// component changes 

		if (Input::GetInstance()->GetKey(GLFW_KEY_LEFT_SHIFT) == KEY_STATE::PRESS) {
			m_mainBody->ScalarMove(glm::vec3{ 0.1f,0.f,0.f });
		}
		else {




			m_firstHand1->Rotate(glm::vec3(0.f, -30.f, 0.f));
			m_firstHand2->Rotate(glm::vec3(0.f, 30.f, 0.f));


			m_secondHand1->Rotate(glm::vec3{ -30.f,0.f,0.f });
			m_secondHand2->Rotate(glm::vec3{ 30.f,0.f,0.f });
		}


	}

	if (Input::GetInstance()->GetKey(GLFW_KEY_G) == KEY_STATE::DOWN) {
		if (Input::GetInstance()->GetKey(GLFW_KEY_LEFT_SHIFT) == KEY_STATE::PRESS) {
			m_mainBody->Rotate(glm::vec3(0.f,-10.f, 0.f));

		}
		else {
			m_mainBody->Rotate(glm::vec3(0.f, 10.f, 0.f));
		}
	}

	if (Input::GetInstance()->GetKey(GLFW_KEY_F) == KEY_STATE::DOWN) {
		if (Input::GetInstance()->GetKey(GLFW_KEY_LEFT_SHIFT) == KEY_STATE::PRESS) {
			m_subBody1->Rotate(glm::vec3(0.f, -30.f, 0.f));

		}
		else {
			m_subBody1->Rotate(glm::vec3(0.f, 30.f, 0.f));
		}

	}


	if (Input::GetInstance()->GetKey(GLFW_KEY_R) == KEY_STATE::PRESS) {

		if (t > 1.f) {
			t_dir = -1.f;
		}
		else if(t < 0.f){
			t_dir = 1.f;
		}

		m_firstHand1->LinearMove(m_firsthand1_P1, m_firsthand1_P2, t);
		m_firstHand2->LinearMove(m_firsthand2_P1, m_firsthand2_P2, t);
		t = t + t_dir * 0.0001f;

	}

	m_mainBody->Update(dt);
	m_firstHand1->Update(dt);
	m_firstHand2->Update(dt);
	m_subBody1->Update(dt);
	m_secondHand1->Update(dt);
	m_secondHand2->Update(dt);

}
