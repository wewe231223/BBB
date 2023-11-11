#pragma once
#include "Mesh.h"
#include "Model.h"


class Tank : public MonoObject {
public:
	Tank(UINT sid, std::shared_ptr<Mesh> mesh);

private:

	std::shared_ptr<Model> m_mainBody{ nullptr };
	std::unique_ptr<Model> m_firstHand1{ nullptr };
	std::unique_ptr<Model> m_firstHand2{ nullptr };

	std::shared_ptr<Model> m_subBody1{ nullptr };
	std::unique_ptr<Model> m_secondHand1{ nullptr };
	std::unique_ptr<Model> m_secondHand2{ nullptr };




public:

	virtual void Render(UINT sid);
	virtual void Update(float dt);

	virtual std::tuple<float3, float3> Get_Bounding_Box() {};

};

