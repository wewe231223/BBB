#include "pch.h"
#include "Robot.h"
#include "Input.h"

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
	m_rightHand->Set(glm::vec3(0.5f, -0.4f, 0.f), Qualifier::PIVOT);
	m_rightHand->Set(glm::vec3(1.5f, 5.f, 1.5f), Qualifier::SCALE);
	




	m_leftHand->Set(glm::vec3(-0.5f, 0.4f, 0.f), Qualifier::POSITION);
	m_leftHand->Set(glm::vec3(-0.5f, -0.4f, 0.f), Qualifier::PIVOT);
	m_leftHand->Set(glm::vec3(1.5f, 5.f, 1.5f), Qualifier::SCALE);



	m_rightLeg->Set(glm::vec3(0.3f, -0.5f, 0.f), Qualifier::POSITION);
	m_rightLeg->Set(glm::vec3(0.f, -0.5f, 0.f), Qualifier::PIVOT);
	m_rightLeg->Set(glm::vec3(1.5f, 5.f, 1.5f), Qualifier::SCALE);



	m_leftLeg->Set(glm::vec3(-0.3f, -0.5f, 0.f), Qualifier::POSITION);
	m_leftLeg->Set(glm::vec3(0.f, -0.5f, 0.f), Qualifier::PIVOT);
	m_leftLeg->Set(glm::vec3(1.5f, 5.f, 1.5f), Qualifier::SCALE);


	m_rightHand->Rotate(glm::vec3(0.f, 0.f, 30.f));
	m_leftHand->Rotate(glm::vec3(0.f, 0.f, 30.f));


}

void Robot::Update(float dt){

	m_rightHand->Update(dt);

	m_leftHand->Update(dt);

}

void Robot::Render(UINT sid)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	m_body->Render(sid);
	m_head->Render(sid);

	m_rightHand->Render(sid);
	m_leftHand->Render(sid);

	m_rightLeg->Render(sid);
	m_leftLeg->Render(sid);



}
