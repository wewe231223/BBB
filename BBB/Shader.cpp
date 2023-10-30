#include "pch.h"
#include "Shader.h"

constexpr auto V_ShaderPath = "Vertex.glsl";
constexpr auto F_ShaderPath = "Fragment.glsl";

Shader::Shader(){
	std::ifstream VertexFileptr = std::ifstream( V_ShaderPath , std::ios::in);
	std::ifstream FragmentFileptr = std::ifstream( F_ShaderPath , std::ios::in);

	std::stringstream Vertexstream = std::stringstream{};
	std::stringstream Fragmentstream = std::stringstream{};


	std::string s1{ " " };
	std::string s2{ " " };
	if (VertexFileptr.is_open()) {
		Vertexstream << VertexFileptr.rdbuf();
		s1 = Vertexstream.str();
	}
	else {
		std::cerr << "ERROR : FAILED TO OPEN FILE " << std::endl;
		exit(EXIT_FAILURE);
	}


	if (FragmentFileptr.is_open()) {
		Fragmentstream << FragmentFileptr.rdbuf();
		s2 = Fragmentstream.str();
	}
	else {
		std::cerr << "ERROR : FAILED TO OPEN FILE " << std::endl;
		exit(EXIT_FAILURE);
	}


	const GLchar* VertexShaderSource = s1.c_str();
	const GLchar* FragmentShaderSource = s2.c_str();



	m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_vertexShaderID, 1, &VertexShaderSource, NULL);
	glCompileShader(m_vertexShaderID);

	GLint result{};
	GLchar errorlog[512]{};

	glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_vertexShaderID, 512, NULL, errorlog);
		std::cerr << "ERROR : VERTEX SHADER COMPILE ERROR" << std::endl;
		std::cerr << errorlog << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cerr << "VERTEX SHADER SUCESSFULLY COMPILED!" << std::endl;
	}




	m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_fragmentShaderID, 1, &FragmentShaderSource, NULL);
	glCompileShader(m_fragmentShaderID);

	ZeroMemory(errorlog, 512);

	glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &result);
	if (!result) {
		glGetShaderInfoLog(m_fragmentShaderID, 512, NULL, errorlog);
		std::cerr << "ERROR : FRAGMENT SHADER COMPILE ERROR" << std::endl;
		std::cerr << errorlog << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cerr << "FRAGMENT SHADER SUCESSFULLY COMPILED!" << std::endl;
	}

	m_shaderID = glCreateProgram();
	glAttachShader(m_shaderID, m_vertexShaderID);
	glAttachShader(m_shaderID, m_fragmentShaderID);

	glLinkProgram(m_shaderID);

	glDeleteShader(m_vertexShaderID);
	glDeleteShader(m_fragmentShaderID);


	ZeroMemory(errorlog, 512);
	glGetProgramiv(m_shaderID, GL_LINK_STATUS, &result);

	if (!result) {
		glGetProgramInfoLog(m_shaderID, 512, NULL, errorlog);
		std::cerr << "ERROR : SHADER LINK FAILED" << std::endl;
		std::cerr << errorlog << std::endl;
		exit(EXIT_FAILURE);
	}
	else {
		std::cerr << "SHADERS SUCESSFULLY CREATED" << std::endl;
	}

	glUseProgram(m_shaderID);

}
