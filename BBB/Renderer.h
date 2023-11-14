#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"
#include "Coord.h"
#include "Rigidbody_.h"


class Renderer{
public:
	Renderer(GLFWwindow* Window);
	~Renderer() = default;

	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;



private:
	GLFWwindow* m_window{ nullptr };

	std::map<std::string,std::shared_ptr<Mesh>> m_meshDict{};
	
	std::vector<std::shared_ptr<Model>> m_modelList{};



	std::map<std::string, std::shared_ptr<Rigidbody>> m_objectDict{};
	std::vector<std::shared_ptr<MonoObject>> m_objectList{};
	
	
	std::unique_ptr<Shader> m_shader{ nullptr };
	std::unique_ptr<Camera> m_camera{ nullptr };
	std::unique_ptr<Coord> m_coord{ nullptr };





public:
	
	void Load(std::string path);



	void Render();
	void Update(float dt);
	



};

