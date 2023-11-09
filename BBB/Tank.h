#pragma once
#include "Mesh.h"
#include "Model.h"


class Tank : public Object {
public:
	Tank(UINT sid, std::shared_ptr<Mesh> mesh);

private:

	std::shared_ptr<Model> m_mainBody{ nullptr };
	std::unique_ptr<Model> m_firstHand1{ nullptr };
	std::unique_ptr<Model> m_firstHand2{ nullptr };

	std::shared_ptr<Model> m_subBody1{ nullptr };
	std::unique_ptr<Model> m_secondHand1{ nullptr };
	std::unique_ptr<Model> m_secondHand2{ nullptr };


	float t{};
	float t_dir = 1.f;


	glm::vec3 m_firsthand1_P1{};
	glm::vec3 m_firsthand2_P1{};

	glm::vec3 m_firsthand1_P2{};
	glm::vec3 m_firsthand2_P2{};



public:

	virtual void Render(UINT sid);
	virtual void Update(float dt);


};

