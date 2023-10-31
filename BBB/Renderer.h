#pragma once

#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"



class Renderer{
public:
	Renderer(GLFWwindow* Window);
	~Renderer() = default;

	Renderer(const Renderer& other) = delete;
	Renderer& operator=(const Renderer& other) = delete;



private:
	GLFWwindow* m_window{ nullptr };

	std::map<std::string, Mesh> m_meshDict{};
	std::vector<Model> m_modelList{};

	std::unique_ptr<Shader> m_shader{ nullptr };
	std::unique_ptr<Camera> m_camera{ nullptr };

public:
	
	void Load(std::string path);



	void Render();
	void Update(float dt);
	



};

