#include "pch.h"
#include "Renderer.h"

Renderer::Renderer(GLFWwindow* Window){
	m_window = Window;
	m_shader = std::make_unique<Shader>();
	m_camera = std::make_unique<Camera>(m_window, m_shader->GetShaderID(), glm::vec3(10.f, 10.f, 10.f), 0.1f, 1000.f);
}

void Renderer::Load(std::string path){

	// teminate old renderer 
	std::vector<Model>().swap(m_modelList);
	std::map<std::string, Mesh>().swap(m_meshDict);


	const char* cpath = path.c_str();




	//Load Scene



}

void Renderer::Render(){

	m_camera->Render(m_shader->GetShaderID());

	for (auto& i : m_modelList) {
		i.Render(m_shader->GetShaderID());
	}

}

void Renderer::Update(float dt){

	m_camera->Update();

	for (auto& i : m_modelList) {
		i.Update(dt);
	}


}



