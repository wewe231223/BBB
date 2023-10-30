#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Shader.h"
#include "Timer.h"

void __default_reshape(GLFWwindow* window, int width, int height);

class Engine {
public:
	Engine();
	~Engine();

private:
	// ������ ������ ���� ����ü
	WINDOWINFORMATION	m_windowInfo{ };

	// ���ҹ����� ���� ������ ������ ���� �⺻�� 0 ������ �Ϸ��� ū���� �ָ� ��
	int32		m_swapInterver{ };


	
	std::unique_ptr<Shader> m_shader = nullptr;
	std::unique_ptr<Timer> m_timer = nullptr;


public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void Loop();
};

#endif // !_ENGINE_H_
