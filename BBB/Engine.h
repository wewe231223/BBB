#ifndef _ENGINE_H_
#define _ENGINE_H_


class Engine {
public:
	Engine();
	~Engine();

private:
	// ������ ������ ���� ����ü
	WINDOWINFO	m_windowInfo{ };

	// ���ҹ����� ���� ������ ������ ���� �⺻�� 0 ������ �Ϸ��� ū���� �ָ� ��
	int32		m_swapInterver{ };

public:
	void Init();
	void Update();
	void LateUpdate();
	void Render();

	void Loop();
};

#endif // !_ENGINE_H_
