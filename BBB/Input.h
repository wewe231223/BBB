#pragma once



class Input{
private:
	Input() = default;
	Input(const Input& other) = delete;
	~Input() = delete;
	Input& operator=(const Input& other) = delete;

private:

	GLFWwindow* m_window{ nullptr };

	// # DO NOT MODIFY THIS PAIR.SECOND #
	std::vector<std::pair<KEY_STATE, int>> m_keys;
		
	float2 m_prevMouse{};
	float2 m_deltaMouse{};


	
	static Input* InputInstance;

public:

	static Input* GetInstance(GLFWwindow* window);
	static Input* GetInstance();

	void Update();

	const KEY_STATE GetKey(int key);
	const float2 GetDeltaMouse() { return m_deltaMouse; };
};

