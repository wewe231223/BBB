#include "pch.h"
#include "Input.h"
#pragma warning(disable: 4002)

Input* Input::InputInstance = nullptr;

Input* Input::GetInstance(GLFWwindow* window){
	
	if (InputInstance == nullptr) {

		InputInstance = new Input;

		InputInstance->m_window = window;
		InputInstance->m_keys.resize(GLFW_KEY_LAST);

		for (auto i = 1; i <= GLFW_KEY_LAST; ++i) {
			int result = glfwGetKeyScancode(i);

			if (result > 0) {
				InputInstance->m_keys.push_back(std::make_pair(KEY_STATE::NONE, i));
			}

		}

		InputInstance->m_keys.shrink_to_fit();
	}


	return InputInstance;
}

Input* Input::GetInstance()
{
	assert(InputInstance != nullptr, __FILE__, __LINE__);	
	return InputInstance;
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

const KEY_STATE Input::GetKey(int key)
{

	for (auto& i : m_keys) {
		if (i.second == key) {
			return i.first;
		}
	}

	
	return KEY_STATE::NONE;
}
