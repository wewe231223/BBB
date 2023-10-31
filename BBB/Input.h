#pragma once



class Input{
public:
	Input(GLFWwindow* window);
	Input(const Input& other) = delete;

	~Input() = default;
	Input& operator=(const Input& other) = delete;
private:

	GLFWwindow* m_window{ nullptr };

	// # DO NOT MODIFY THIS PAIR.SECOND #
	std::vector<std::pair<KEY_STATE, int>> m_keys;

	double m_mouseX{};
	double m_mouseY{};



public:

	void Update();


	

};

