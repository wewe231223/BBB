#include "pch.h"
#include "Input.h"




Input::Input(GLFWwindow* window){

	m_window = window;

	m_keys.resize(GLFW_KEY_LAST);


	// resister key for printable
	for (auto i = 1; i <= GLFW_KEY_LAST; ++i) {
		int result = glfwGetKeyScancode(i);

		if (result > 0) {
			m_keys.push_back(std::make_pair(KEY_STATE::NONE, i));
		}

	}

	m_keys.shrink_to_fit();
}



void Input::Update(){
	glfwGetCursorPos(m_window, &m_mouseX, &m_mouseY);

	for (auto& i : m_keys) {
		if (glfwGetKey(m_window, i.second) == GLFW_PRESS) {
			// if key press


			// if pressed, prev state is released or none
			if (i.first == KEY_STATE::NONE or i.first == KEY_STATE::RELEASE) {
				i.first = KEY_STATE::DOWN;
				std::cout << i.second << ": is first press" << std::endl;
			}
			else if (i.first == KEY_STATE::DOWN) {
				i.first = KEY_STATE::PRESS;
				std::cout << i.second << ": is being press" << std::endl;
			}

		}
		else {
			if (i.first == KEY_STATE::PRESS or i.first == KEY_STATE::DOWN) {
				i.first = KEY_STATE::RELEASE;
				std::cout << i.second << ": is released" << std::endl;

			}
			else {
				i.first = KEY_STATE::NONE;
			}
		}
	}


	//std::cout << m_mouseX << " , " << m_mouseY << std::endl;

}
