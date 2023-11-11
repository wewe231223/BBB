#include "pch.h"
#include "Box.h"

Box::Box(UINT sid, std::shared_ptr<Mesh> mesh){

	m_body = std::make_unique<Model>(sid, mesh->GetMesh(), mesh->GetVertexCount());

	m_body->Set(glm::vec3{ 0.f,1.f,0.f }, Qualifier::POSITION);
	m_body->Set(glm::vec3{ 1.f,1.f,1.f }, Qualifier::SCALE);




}
