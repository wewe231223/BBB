#include "pch.h"
#include "Tank.h"
#include "Input.h"

Tank::Tank(UINT sid, std::shared_ptr<Mesh> mesh){

	m_mainBody = std::make_shared<Model>(sid, mesh->GetMesh(),mesh->GetVertexCount());

	m_firstHand1 = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_firstHand2 = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());


	m_subBody1 = std::make_shared<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());

	m_secondHand1 = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());
	m_secondHand2 = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());


	m_mainBody->Set(glm::vec3(0.f, 5.f, 0.f), Qualifier::POSITION);
	m_mainBody->Set(glm::vec3(0.f, 0.f, 0.f), Qualifier::ROTATION);
	m_mainBody->Set(float3{ 2.f,2.f,10.f }, Qualifier::SCALE);



	m_firstHand1->Set(glm::vec3(7.f, 0.f, 0.3f), Qualifier::POSITION);
	m_firstHand1->Set(float3{ 3.f,0.7f,0.7f }, Qualifier::SCALE);
	m_firstHand1->Set(m_mainBody, Qualifier::PARENT);





}

void Tank::Render(UINT sid){

	
	m_mainBody->Render(sid);
	//m_firstHand1->Render(sid);



}

void Tank::Update(float dt){
	m_mainBody->Rotate(glm::vec3(0.f, 80.f * dt, 0.f));

	if (Input::GetInstance()->GetKey(GLFW_KEY_LEFT) == KEY_STATE::PRESS) {
		// component changes 

		m_mainBody->Rotate(glm::vec3(0.f, 10.f * dt, 0.f));
		m_firstHand1->Rotate(glm::vec3(0.f,10.f * dt,0.f));
	}

	if (Input::GetInstance()->GetKey(GLFW_KEY_RIGHT) == KEY_STATE::PRESS) {
		// component changes 
		m_mainBody->Rotate(glm::vec3(0.f, -10.f * dt, 0.f));

		m_firstHand1->Rotate(glm::vec3(0.f, 10.f * -dt, 0.f));
	}



}
