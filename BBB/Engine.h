#ifndef _ENGINE_H_
#define _ENGINE_H_

#include "Shader.h"

void __default_reshape(GLFWwindow* window, int width, int height);

class Engine {
public:
	Engine();
	~Engine();

private:
	// 윈도우 정보를 담을 구조체
	WINDOWINFO	m_windowInfo{ };

	// 스왑버퍼의 스왑 간격을 조정할 변수 기본은 0 느리게 하려면 큰값을 주면 됨
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
