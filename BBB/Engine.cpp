#include "pch.h"
#include "Engine.h"

Engine::Engine() { }

Engine::~Engine() { }

void Engine::Init() {
	// glfw ���̺귯�� �ʱ�ȭ
	if (!glfwInit()) {
		exit(-1);
	}

	// OpenGL ���� ����
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// ������ ���� �ʱ� ����
	m_windowInfo.width = 1920;
	m_windowInfo.height = 1080;
	m_windowInfo.x = 0;
	m_windowInfo.y = 0;
	m_windowInfo.windowTitle = "FPS: ";

	// ������ ����
	m_windowInfo.window = glfwCreateWindow(m_windowInfo.width, m_windowInfo.height, m_windowInfo.windowTitle.c_str(), NULL, NULL);
	if (m_windowInfo.window == nullptr) {
		glfwTerminate();
		exit(-1);
	}

	// ������ �����츦 ���� ���� ������� ����
	glfwMakeContextCurrent(m_windowInfo.window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		exit(-1);
	}

	// ����Ʈ ����
	glViewport(0, 0, m_windowInfo.width, m_windowInfo.height);

	glfwSwapInterval(m_swapInterver);



	m_shader = std::make_unique<Shader>();
	m_timer = std::make_unique<Timer>();
	m_input = std::make_unique<Input>(m_windowInfo.window);


	// resister callbacks 
	glfwSetFramebufferSizeCallback(m_windowInfo.window, __default_reshape);

	glfwSetKeyCallback(m_windowInfo.window, __default_keyboard);
}

void Engine::Update() {
	// ���� ������Ʈ �Լ�

	//int result = glfwGetKey(m_windowInfo.window, GLFW_KEY_SPACE);

	//if (result == GLFW_PRESS) {
	//	std::cout << "Press!" << std::endl;
	//}
	//else if (result == GLFW_RELEASE) {
	//	std::cout << "Release!" << std::endl;

	//}
	//else {
	//	std::cout << "None!" << std::endl;
	//}

	m_timer->Update();
	glfwSetWindowTitle(m_windowInfo.window, ((m_windowInfo.windowTitle) + std::to_string(m_timer->GetFps())).c_str() );

	m_input->Update();


}

void Engine::LateUpdate() {
	// ���� ������Ʈ�� ȣ���ϰ�
	// �߰��� �� ������Ʈ�� ����� �� ���� ����� �̰��� �ۼ�
	// ������Ʈ�� ������ ��Ȯ�� �����ϱ� ���� ���̴� �Լ� ex) ������Ʈ ����
}

void Engine::Render() {
	//// ������ �ڵ�
	glClearColor(0.f,0.f,0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glfwSwapBuffers(m_windowInfo.window);
}

void Engine::Loop() {
	while (!glfwWindowShouldClose(m_windowInfo.window)) {

		Update();

		LateUpdate();

		Render();

		glfwPollEvents();
		

	}
}

void __default_reshape(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void __default_keyboard(GLFWwindow* window, int key, int scanCode, int action, int mode) {


	

}