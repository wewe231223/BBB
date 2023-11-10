#pragma once
#include "Mesh.h"
#include "Model.h"


class Robot : public Object{

public:
	Robot(UINT sid, std::shared_ptr<Mesh> mesh);



private:
	std::shared_ptr<Model> m_body{nullptr};



	// final model 
	std::unique_ptr<Model> m_head{ nullptr };


	//
	std::unique_ptr<Model> m_rightHand{ nullptr };
	std::unique_ptr<Model> m_leftHand{ nullptr };

	std::unique_ptr<Model> m_rightLeg{ nullptr };
	std::unique_ptr<Model> m_leftLeg{ nullptr };


public:

	virtual void Update(float dt);
	virtual void Render(UINT sid);



};

