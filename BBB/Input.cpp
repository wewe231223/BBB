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


		double tx_, ty_;
		glfwGetCursorPos(InputInstance->m_window, &tx_, &ty_);

		InputInstance->m_prevMouse.x = static_cast<float>(tx_);
		InputInstance->m_prevMouse.y = static_cast<float>(ty_);




		/* new key state part */




		InputInstance->m_keyboard = new KEY_STATE[255];	
		ZeroMemory(InputInstance->m_keyboard, 255);


		/*
		

		넣을때 조금 손해보더라도 map 이 키 검색에 유리?

		VK 가 연속적?
		
		이러면 맵이 나을듯



		VK가 연속적인 수가 아니라면 벡터에 넣고 찾을때 순회 비교?	

		*/
	}


	return InputInstance;
}

Input* Input::GetInstance()
{
	assert(InputInstance != nullptr, __FILE__, __LINE__);	
	return InputInstance;
}





void Input::Update(){

	for (auto& i : m_keys) {
		if (glfwGetKey(m_window, i.second) == GLFW_PRESS) {
			// if key press


			// if pressed, prev state is released or none
			if (i.first == KEY_STATE::NONE or i.first == KEY_STATE::RELEASE) {
				i.first = KEY_STATE::DOWN;
			}
			else if (i.first == KEY_STATE::DOWN) {
				i.first = KEY_STATE::PRESS;
			}

		}
		else {
			if (i.first == KEY_STATE::PRESS or i.first == KEY_STATE::DOWN) {
				i.first = KEY_STATE::RELEASE;

			}
			else {
				i.first = KEY_STATE::NONE;
			}
		}



		if (i.first == KEY_STATE::DOWN and i.second == GLFW_KEY_ESCAPE) {

			// now, ESCAPE key to end loop
			glfwSetWindowShouldClose(m_window, GLFW_TRUE);
		}

	}



	/* new input part */



	//BYTE temp_keyboard[256]{};

	//assert(GetKeyboardState(temp_keyboard));

	//


	//for (auto i = 0; i < 256; ++i) {


	//	if (temp_keyboard[i] & 0x80) {
	//		std::cout << "press" << std::endl;
	//	}


	//}
	//







	double tx_, ty_;


	glfwGetCursorPos(m_window, &tx_, &ty_);

	m_deltaMouse.x = static_cast<float>(tx_) - m_prevMouse.x;
	m_deltaMouse.y = static_cast<float>(ty_) - m_prevMouse.y;

	m_prevMouse.x = static_cast<float>(tx_);
	m_prevMouse.y = static_cast<float>(ty_);





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
