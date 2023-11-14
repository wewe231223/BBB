#include "pch.h"
#include "Box.h"

Box::Box(UINT sid, std::shared_ptr<Mesh> mesh){

	m_body = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());

	m_body->Set(glm::vec3{ 0.f,1.f,0.f }, Qualifier::POSITION);
	Scale(glm::vec3{ 1.f,1.f,1.f });
}

void Box::Scale(glm::vec3 Scale)
{
	m_body->Set(Scale, Qualifier::SCALE);


	m_bounding_Box_Left_Bottom = float3{ m_bounding_Box_Left_Bottom.x * Scale.x , m_bounding_Box_Left_Bottom.y * Scale.y , m_bounding_Box_Left_Bottom.z * Scale.z };
	m_bounding_Box_Right_Top = float3{ m_bounding_Box_Right_Top.x * Scale.x ,m_bounding_Box_Right_Top.y * Scale.y ,m_bounding_Box_Right_Top.z * Scale.z };



}
