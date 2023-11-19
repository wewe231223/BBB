#include "pch.h"
#include "Box.h"
#include "Input.h"

Box::Box(UINT sid, std::shared_ptr<Mesh> mesh){

	m_body = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());

	m_position = glm::vec3{ 1.f,0.f,1.f };
	m_body->Set(m_position, Qualifier::POSITION);
	
	m_body->Set(glm::vec3{ 0.f,90.f,0.f }, Qualifier::MAX_ROTATION);
	

	m_volumeX = 0.5f;
	m_volumeY = 0.5f;
	m_volumeZ = 0.5f;


}






void Box::Scale(glm::vec3 Scale)
{
	m_body->Set(Scale, Qualifier::SCALE);


	m_volumeX *= Scale.x;
	m_volumeY *= Scale.y;
	m_volumeZ *= Scale.z;


}

void Box::Render(UINT sid)
{
	m_body->Render(sid);



	//RenderVector(sid, m_position, m_axisX * m_volumeX, float3{1.f,0.f,0.f});
	//RenderVector(sid, m_position, m_axisY * m_volumeY, float3{ 0.f,1.f,0.f });
	//RenderVector(sid, m_position, m_axisZ * m_volumeZ, float3{ 0.f,0.f,1.f });


}

void Box::Update(float dt)
{

	
	if (!m_gravity) {
		//m_body->SetRevolution(glm::vec3{ 0.f,0.f,1.f * dt });
		m_body->Rotate(glm::vec3{ 30.f,0.f,0.f });
		m_position = glm::mat4{ glm::yawPitchRoll(0.f,0.f, glm::radians(30.f * dt)) } * glm::vec4{ m_position ,1.f };
	}


	if (Input::GetInstance()->GetKey(GLFW_KEY_SPACE) == KEY_STATE::DOWN) {
		m_body->Rotate(glm::vec3{ 0.f,0.f,0.f });
	}

	if (m_gravity) {
		m_deltaPosition = glm::vec3{ 0.f,-9.8f * dt,0.f };
		m_position += m_deltaPosition;
		Rigidbody::Update(dt);


	}


	//m_position = glm::yawPitchRoll(glm::radians(10.f * dt), 0.f, 0.f) * glm::vec4{m_position,1.f};
	m_body->Set(m_position, Qualifier::POSITION);
	
	
	m_body->Update(dt);



}
