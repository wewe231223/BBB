#pragma once
#include "Mesh.h"
#include "Model.h"



class Box final : public MonoObject{
private:

	
	std::unique_ptr<Model> m_body{nullptr};


	glm::vec3 m_position{ 0.f,1.f,0.f };




	float3 m_bounding_Box_Left_Bottom{m_position.x - 0.5f,m_position.y - 0.5f,m_position.z - 0.5f};
	float3 m_bounding_Box_Right_Top{ m_position.x + 0.5f,m_position.y + 0.5f,m_position.z + 0.5f };





public:
	Box(UINT sid, std::shared_ptr<Mesh> mesh);

	virtual void Render(UINT sid) { m_body->Render(sid); RenderCube(sid, m_bounding_Box_Left_Bottom, m_bounding_Box_Right_Top); };
	virtual void Update(float dt) {};
	std::tuple<float3, float3> Get_Bounding_Box() { return std::make_tuple(m_bounding_Box_Left_Bottom, m_bounding_Box_Right_Top); };

};

