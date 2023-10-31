#include "pch.h"
#include "Renderer.h"
#pragma warning(disable: 4002)

Renderer::Renderer(GLFWwindow* Window){
	m_window = Window;
	m_shader = std::make_unique<Shader>();
	m_camera = std::make_unique<Camera>(m_window, m_shader->GetShaderID(), glm::vec3(0.f, 0.f, 10.f), 0.1f, 1000.f);
}

void Renderer::Load(std::string path){

	// teminate old renderer 
	std::vector<Model>().swap(m_modelList);
	std::map<std::string, std::shared_ptr<Mesh>>().swap(m_meshDict);


	const char* cpath = path.c_str();
	//Load Scene

	std::fstream file(path.c_str());


	assert(file.is_open(), __FILE__, __LINE__);

	

	std::string head{};


	while (!file.eof()) {

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

				Model m(m_shader->GetShaderID(), iter->second->GetMesh(), iter->second->GetVertexCount());
				m_modelList.push_back(m);

			}


		}


	}
	



}

void Renderer::Render(){

	m_camera->Render(m_shader->GetShaderID());

	for (auto& i : m_modelList) {
		i.Render(m_shader->GetShaderID());
	}

}

void Renderer::Update(float dt){

	m_camera->Update(dt);

	for (auto& i : m_modelList) {
		i.Update(dt);
	}


}



