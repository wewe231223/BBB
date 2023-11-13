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
	m_camera = std::make_unique<Camera>(m_window, m_shader->GetShaderID(), glm::vec3(0.f, 0.f, 10.f), 0.1f, 1000.f);
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
				m_objectList.push_back(std::make_shared<Robot>(m_shader->GetShaderID(), iter->second));
				m_objectDict.insert(std::make_pair(ObjectTag, newRobot));
			}
			else if (objectName._Equal("Box")) {
				std::shared_ptr<Box> newBox = std::make_shared<Box>(m_shader->GetShaderID(), iter->second);
				m_objectList.push_back(std::make_shared<Box>(m_shader->GetShaderID(), iter->second));
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

			target->second->Add_Collide(source->second);









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



