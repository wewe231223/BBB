#pragma once
#include "Mesh.h"
#include "Model.h"

#include "Rigidbody_.h"

class Box final : public Rigidbody{
private:

	
	std::unique_ptr<Model> m_body{nullptr};




	bool m_gravity = false;




public:
	Box(UINT sid, std::shared_ptr<Mesh> mesh);

	void Scale(glm::vec3 Scale);

	void SetPivot(glm::vec3 p) { m_body->Set(p, Qualifier::PIVOT); }
	void SetRotateDirection(float d) { m_body->SetRotateDir(d); }


	

	bool m_p_isMove = false;
	bool m_p_isRevolution = false;

	void EnableGravity() { m_gravity = true; }


	virtual void Render(UINT sid);
	virtual void Update(float dt);

};

