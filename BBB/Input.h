#pragma once
#define DEL delete;

class Input{
public:
	Input();
	Input(const Input& other) = delete;

	~Input();
	Input& operator=(const Input& other) = delete;
private:
	bool* m_keys{ nullptr };





};

