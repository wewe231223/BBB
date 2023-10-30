#include "pch.h"
#include "Input.h"

enum class KEY_STATE {
	NONE,
	PRESS,
	DOWN,
	RELEASE
};



Input::Input(GLFWwindow* window){

	m_window = window;

	m_keys = new KEY_STATE[GLFW_KEY_LAST];
	
	memset(m_keys, 0, GLFW_KEY_LAST * 4);



	
}

Input::~Input(){

	KEY_STATE* tp = m_keys;
	m_keys = nullptr;
	delete[] tp;

}

void Input::Update(){

	




}
