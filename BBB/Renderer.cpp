#include "pch.h"
#include "Renderer.h"
#pragma warning(disable: 4002)


#include "Tank.h"
#include "Robot.h"
#include "box.h"

Renderer::Renderer(GLFWwindow* Window){
	m_window = Window;
	m_shader = std::make_unique<Shader>();
	m_coord = std::make_unique<Coord>();
	m_camera = std::make_unique<Camera>(m_window, m_shader->GetShaderID(), glm::vec3(1.f, 1.f, 10.f), 0.1f, 1000.f);
}

void Renderer::Load(std::string path){

	// teminate old renderer 
	std::vector<std::shared_ptr<Model>>().swap(m_modelList);
	std::map<std::string, std::shared_ptr<Mesh>>().swap(m_meshDict);

	std::shared_ptr<Model> parent = nullptr;

	const char* cpath = path.c_str();
	//Load Scene

	std::fstream file(path.c_str());


	assert(file.is_open(), __FILE__, __LINE__);

	

	std::string head{};


	while (!file.eof()) {
		head.clear();
		file >> head;
		if (head._Equal("Mesh")) {
			std::string meshPath,meshName{};

			file >> meshPath >> meshName;
			m_meshDict.insert(std::make_pair(meshName, std::make_shared<Mesh>(meshPath) ));
		}


		if (head._Equal("Model")) {

			std::string meshName{};

			file >> meshName;

			if (!meshName.empty()) {
				auto iter = m_meshDict.find(meshName);

				assert(!(iter == m_meshDict.end()), __FILE__, __LINE__);




				std::shared_ptr<Model> m = std::make_shared<Model>(m_shader->GetShaderID(), iter->second->GetMesh(), iter->second->GetVertexCount());

				if (parent != nullptr) {
					m->Set(parent, Qualifier::PARENT);
				}

				m_modelList.push_back(m);

			}




		}

		if (head._Equal("Object")) {

			std::string objectName, meshName, ObjectTag{};



			file >> objectName >> meshName >> ObjectTag;

			



			auto iter = m_meshDict.find(meshName);
			assert(!(iter == m_meshDict.end()), __FILE__, __LINE__);


			if (objectName._Equal("Tank")) {
				// ÅÊÅ© º¸·ù 
				//m_objectList.push_back(std::make_shared<Tank>(m_shader->GetShaderID(), iter->second));
			}
			else if (objectName._Equal("Robot")) {
				std::shared_ptr<Robot> newRobot = std::make_shared<Robot>(m_shader->GetShaderID(), iter->second);
				m_objectDict.insert(std::make_pair(ObjectTag, newRobot));
			}
			else if (objectName._Equal("Box")) {
				std::shared_ptr<Box> newBox = std::make_shared<Box>(m_shader->GetShaderID(), iter->second);
				m_objectDict.insert(std::make_pair(ObjectTag, newBox));
			}
			else {
				std::cerr << objectName << " : Not Found" << std::endl;
			}

		}




		if (head._Equal("<Collide>")) {
			std::string targetName, SourceName{};

			file >> targetName >> SourceName;


			auto target = m_objectDict.find(targetName);
			auto source = m_objectDict.find(SourceName);


			assert(target != m_objectDict.end());
			assert(source != m_objectDict.end());

			std::cout << targetName << " " << SourceName << std::endl;

			target->second->AddCollide(source->second);









		}




		if (head._Equal("->Position")) {

			glm::vec3 pos{};


			file >> pos.x >> pos.y >> pos.z;

			assert(m_modelList.size() != 0, __FILE__, __LINE__);


			m_modelList.back()->Set(pos, Qualifier::POSITION);



		}
		if (head._Equal("->Rotation")) {

			glm::vec3 rot{};


			file >> rot.x >> rot.y >> rot.z;

			assert(m_modelList.size() != 0, __FILE__, __LINE__);


			m_modelList.back()->Set(rot, Qualifier::ROTATION);



		}

		if (head._Equal("->Scale")) {

			glm::vec3 scale{0.f,0.f,0.f};


			file >> scale.x >> scale.y >> scale.z;


			assert(m_modelList.size() != 0, __FILE__, __LINE__);


		
			m_modelList.back()->Set(scale, Qualifier::SCALE);

		}

		if (head._Equal("{")) {
			parent = m_modelList.back();
		}

		if (head._Equal("}")) {
			if (parent != nullptr) {
				parent = parent->GetParent();
			}
		}


	}
	



}

void Renderer::Render(){

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	m_camera->Render(m_shader->GetShaderID());
	m_coord->Render(m_shader->GetShaderID());
	
	for (const auto& [key,value] : m_objectDict) {
		value->Render(m_shader->GetShaderID());
	}

//	RenderCube(m_shader->GetShaderID(), float3{ 50.f,50.f,50.f }, float3{ 100.f,100.f,100.f });


}

void Renderer::Update(float dt){

	m_camera->Update(dt);
	
	for (const auto& [key, value] : m_objectDict) {
		value->Update(dt);
	}


	



}



void Renderer::Solution24()
{

	std::shared_ptr<Mesh> CubeMesh = std::make_shared<Mesh>("cube.obj");

	std::shared_ptr<Mesh> RedCube = std::make_shared<Mesh>("cube.obj", float3{ 1.f,0.f,0.f });
	std::shared_ptr<Mesh> BlueCube = std::make_shared<Mesh>("cube.obj", float3{ 0.f,0.f,1.f });


	std::shared_ptr<Robot> MainRobot = std::make_shared<Robot>(m_shader->GetShaderID(), CubeMesh);

	MainRobot->Movement(glm::vec3{ 10.f,6.f,10.f });
	m_objectDict.insert(std::make_pair(std::string("MainRobot"), MainRobot));


	

	std::shared_ptr<Box> newBox{ nullptr };

	for (auto i = 0; i < 32; ++i) {
		for (auto j = 0; j < 32; ++j) {

			if ((i + j) % 2 == 0) {
				newBox = std::make_shared<Box>(m_shader->GetShaderID(), RedCube);
			}
			else {
				newBox = std::make_shared<Box>(m_shader->GetShaderID(), BlueCube);
			}

			m_objectDict.insert(std::make_pair(std::to_string(i*1000+j)  , newBox));
			newBox->Movement(glm::vec3{ (float)j,0.f,(float)i });
			MainRobot->AddCollide(newBox);




		}
	}






	newBox = std::make_shared<Box>(m_shader->GetShaderID(), CubeMesh);
	newBox->Movement(glm::vec3(-0.5f, 5.f, 15.5f));
	newBox->Scale(glm::vec3{ 0.1f,10.f,32.f });
	m_objectDict.insert(std::make_pair(std::string("wall1"), newBox));
	MainRobot->AddCollide(newBox);


	newBox = std::make_shared<Box>(m_shader->GetShaderID(), CubeMesh);
	newBox->Movement(glm::vec3(31.5f, 5.f, 15.5f));
	newBox->Scale(glm::vec3{ 0.1f,10.f,32.f });
	m_objectDict.insert(std::make_pair(std::string("wall2"), newBox));
	MainRobot->AddCollide(newBox);


	newBox = std::make_shared<Box>(m_shader->GetShaderID(), CubeMesh);
	newBox->Movement(glm::vec3(15.5f, 5.f, -0.5f));
	newBox->Scale(glm::vec3{ 32.f,10.f,0.1f });
	m_objectDict.insert(std::make_pair(std::string("wall3"), newBox));
	MainRobot->AddCollide(newBox);


	newBox = std::make_shared<Box>(m_shader->GetShaderID(), CubeMesh);
	newBox->Movement(glm::vec3(15.5f, 10.f, 15.5f));
	newBox->Scale(glm::vec3{ 32.f,0.1f,32.f });
	m_objectDict.insert(std::make_pair(std::string("wall4"), newBox));
	MainRobot->AddCollide(newBox);


	

	newBox = std::make_shared<Box>(m_shader->GetShaderID(), CubeMesh);
	
	

	newBox->Movement(glm::vec3(31.5f, 5.f, 31.5f));
	newBox->Scale(glm::vec3{ 16.f,10.f,0.1f });
	newBox->SetPivot(glm::vec3{ -0.5f,0.f,0.f });

	newBox->m_p_isMove = true;


	m_objectDict.insert(std::make_pair(std::string("door1"), newBox));
	MainRobot->AddCollide(newBox);



	newBox = std::make_shared<Box>(m_shader->GetShaderID(), CubeMesh);

	newBox->Movement(glm::vec3(-0.5f, 5.f, 31.5f));
	newBox->Scale(glm::vec3{ 16.f,10.f,0.1f });
	newBox->SetPivot(glm::vec3{ 0.5f,0.f,0.f });
	newBox->SetRotateDirection(-1.f);


	newBox->m_p_isMove = true;
	m_objectDict.insert(std::make_pair(std::string("door2"), newBox));
	MainRobot->AddCollide(newBox);



	newBox = std::make_shared<Box>(m_shader->GetShaderID(), CubeMesh);
	newBox->Movement(glm::vec3{ 10.f,2.f,10.f });

	
	m_objectDict.insert(std::make_pair(std::string("obstacle1"), newBox));
	MainRobot->AddCollide(newBox);


}

void Renderer::Solution23(){


	std::shared_ptr<Mesh> BoardCube  = std::make_shared<Mesh>("cube.obj", float3{ 1.f,0.5f,0.5f });
	std::shared_ptr<Mesh> BoardCube1  = std::make_shared<Mesh>("cube.obj", float3{ 0.5f,1.f,0.5f });
	std::shared_ptr<Mesh> BoardCube2 = std::make_shared<Mesh>("cube.obj", float3{ 0.5f,0.5f,1.f });
	std::shared_ptr<Mesh> BoardCube3 = std::make_shared<Mesh>("cube.obj", float3{ 1.f,0.5f,1.f });

	std::shared_ptr<Mesh> BoxCube1 = std::make_shared<Mesh>("cube.obj", float3{ 1.f,1.f,1.f });

	std::shared_ptr<Box> Mainbox = std::make_shared<Box>(m_shader->GetShaderID(), BoxCube1);
	Mainbox->Movement(glm::vec3{ 0.f,0.f,0.f });
	Mainbox->EnableGravity();
	m_objectDict.insert(std::make_pair(std::string("Mainbox1"), Mainbox));

	
	std::shared_ptr<Box>Boxptr{ nullptr };

	Boxptr = std::make_shared<Box>(m_shader->GetShaderID(), BoardCube);
	Boxptr->Scale(glm::vec3{ 10.f,0.1f,10.f });
	Boxptr->Movement(glm::vec3{ 0.f,-5.f,0.f });
	Mainbox->AddCollide(Boxptr);

	m_objectDict.insert(std::make_pair(std::string("board1"), Boxptr));


	Boxptr = std::make_shared<Box>(m_shader->GetShaderID(), BoardCube1);
	Boxptr->Scale(glm::vec3{ 0.1f,10.f,10.f });
	Boxptr->Movement(glm::vec3{ 5.f,0.f,0.f });

	Boxptr->m_p_isRevolution = true;
	Mainbox->AddCollide(Boxptr);

	m_objectDict.insert(std::make_pair(std::string("board2"), Boxptr));



	Boxptr = std::make_shared<Box>(m_shader->GetShaderID(), BoardCube2);
	Boxptr->Scale(glm::vec3{ 0.1f,10.f,10.f });
	Boxptr->Movement(glm::vec3{ -5.f,0.f,0.f });
	Mainbox->AddCollide(Boxptr);

	m_objectDict.insert(std::make_pair(std::string("board3"), Boxptr));



	Boxptr = std::make_shared<Box>(m_shader->GetShaderID(), BoardCube3);
	Boxptr->Scale(glm::vec3{ 10.f,0.1f,10.f });
	Boxptr->Movement(glm::vec3{ 0.f,5.f,0.f });
	Mainbox->AddCollide(Boxptr);

	m_objectDict.insert(std::make_pair(std::string("board4"), Boxptr));





}



