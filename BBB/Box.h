#pragma once
#include "Mesh.h"
#include "Model.h"

#include "Rigidbody_.h"

class Box final : public Rigidbody{
private:

	
	std::unique_ptr<Model> m_body{nullptr};









public:
	Box(UINT sid, std::shared_ptr<Mesh> mesh);

	void Scale(glm::vec3 Scale);

	virtual void Render(UINT sid);
	virtual void Update(float dt) {};

};

