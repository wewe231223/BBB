#pragma once


enum class KEY_STATE;

class Input{
public:
	Input(GLFWwindow* window);
	Input(const Input& other) = delete;

	~Input();
	Input& operator=(const Input& other) = delete;
private:

	GLFWwindow* m_window{ nullptr };


	KEY_STATE* m_keys{ nullptr };

public:

	void Update();




};

