#include "pch.h"
#include "Engine.h"

Engine::Engine() { }

Engine::~Engine() { }

void Engine::Init() {
	// glfw 라이브러리 초기화
	if (!glfwInit()) {
		exit(-1);
	}

	// OpenGL 버전 설정
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	// 윈도우 정보 초기 설정
	m_windowInfo.width = 1920;
	m_windowInfo.height = 1080;
	m_windowInfo.x = 0;
	m_windowInfo.y = 0;
	m_windowInfo.windowTitle = "FPS: ";

	// 윈도우 생성
	m_windowInfo.window = glfwCreateWindow(m_windowInfo.width, m_windowInfo.height, m_windowInfo.windowTitle.c_str(), NULL, NULL);
	if (m_windowInfo.window == nullptr) {
		glfwTerminate();
		exit(-1);
	}

	// 생성한 윈도우를 현재 메인 윈도우로 설정
	glfwMakeContextCurrent(m_windowInfo.window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		exit(-1);
	}

	// 뷰포트 설정
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
	// 게임 업데이트 함수

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
	// 게임 업데이트를 호출하고
	// 추가로 더 업데이트를 해줘야 할 일이 생기면 이곳에 작성
	// 업데이트와 순서를 명확히 구분하기 위해 쓰이는 함수 ex) 오브젝트 삭제
}

void Engine::Render() {
	//// 렌더링 코드
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