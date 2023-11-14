#include "pch.h"
#include "Box.h"

Box::Box(UINT sid, std::shared_ptr<Mesh> mesh){

	m_body = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());


	m_position = glm::vec3{ 1.f,0.f,1.f };
	m_body->Set(m_position, Qualifier::POSITION);
	
	

	m_volumeX = 0.5f;
	m_volumeY= 0.5f;
	m_volumeZ = 0.5f;


}

void Box::Scale(glm::vec3 Scale)
{
	m_body->Set(Scale, Qualifier::SCALE);





}

void Box::Render(UINT sid)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	m_body->Render(sid);




	RenderVector(sid, m_position, m_axisX * m_volumeX, float3{ 1.f,0.f,0.f });
	RenderVector(sid, m_position, m_axisY * m_volumeY, float3{ 0.f,1.f,0.f });
	RenderVector(sid, m_position, m_axisZ * m_volumeZ, float3{ 0.f,0.f,1.f });

	RenderVector(sid, m_position, -m_axisX * m_volumeX, float3{ 1.f,0.f,0.f });
	RenderVector(sid, m_position, -m_axisY * m_volumeY, float3{ 0.f,1.f,0.f });
	RenderVector(sid, m_position, -m_axisZ * m_volumeZ, float3{ 0.f,0.f,1.f });



}
