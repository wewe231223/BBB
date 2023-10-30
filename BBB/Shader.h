#pragma once
class Shader{

private:
	unsigned int m_vertexShaderID{};
	unsigned int m_fragmentShaderID{};
	unsigned int m_shaderID{};


public:

	Shader();

	unsigned int GetShaderID();

};

