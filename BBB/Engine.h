#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Shader.h"

void __default_reshape(GLFWwindow* window, int width, int height);

class Engine {
public:
	Engine();
	~Engine();

private:
	// ������ ������ ���� ����ü
	WINDOWINFO	m_windowInfo{ };

	// ���ҹ����� ���� ������ ������ ���� �⺻�� 0 ������ �Ϸ��� ū���� �ָ� ��
	int32		m_swapInterver{ };


	
	std::unique_ptr<Shader> m_shader = nullptr;

public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void Loop();
};

#endif // !_ENGINE_H_
