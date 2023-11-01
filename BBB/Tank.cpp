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
	m_mainBody->Set(float3{ 5.f,2.f,5.f }, Qualifier::SCALE);



	m_firstHand1->Set(glm::vec3(0.7f, 0.f, 0.3f), Qualifier::POSITION);
	m_firstHand1->Set(float3{ 0.7f,0.5f,0.2f }, Qualifier::SCALE);
	m_firstHand1->Set(m_mainBody, Qualifier::PARENT);


	m_firstHand2->Set(glm::vec3(0.7f, 0.f, -0.3f), Qualifier::POSITION);
	m_firstHand2->Set(float3{ 0.7f,0.5f,0.2f }, Qualifier::SCALE);
	m_firstHand2->Set(m_mainBody, Qualifier::PARENT);

	
	m_subBody1->Set(glm::vec3(0.f, 0.6f, 0.f),Qualifier::POSITION);
	m_subBody1->Set(float3{ 0.7f,0.6f,0.7f }, Qualifier::SCALE);
	m_subBody1->Set(m_mainBody, Qualifier::PARENT);

	m_secondHand1->Set(glm::vec3(0.f, 1.f, 0.3f), Qualifier::POSITION);
	m_secondHand1->Set(float3{ 0.2f,2.f,0.2f }, Qualifier::SCALE);
	m_secondHand1->Set(m_subBody1, Qualifier::PARENT);

	m_secondHand2->Set(glm::vec3(0.f, 1.f, -0.3f), Qualifier::POSITION);
	m_secondHand2->Set(float3{ 0.2f,2.f,0.2f }, Qualifier::SCALE);
	m_secondHand2->Set(m_subBody1, Qualifier::PARENT);





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

	if (Input::GetInstance()->GetKey(GLFW_KEY_A) == KEY_STATE::PRESS) {
		// component changes 
	}




}
