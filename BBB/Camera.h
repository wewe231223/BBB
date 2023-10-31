#pragma once

constexpr auto MOUSE_SENSITIVE = 20.f;


class Camera{
public:
	Camera(GLFWwindow* Window, UINT ShaderId, glm::vec3 EYE, float NearZ, float FarZ) ;


	~Camera() = default;

	Camera(const Camera& other) = delete;
	Camera& operator=(const Camera& other) = delete;

private:
	UINT m_shaderId{0};
	UINT m_projectionLocation{ 0 };
	UINT m_lookatLocation{ 0 };


	float m_fovY{ 45.f };
	
	glm::vec3 m_eye{ };
	glm::vec3 m_at{0.f,0.f,-1.f};
	glm::vec3 m_up{ 0.f, 1.f, 0.f };
	
	glm::vec3 m_basisX{ 0.f };
	glm::vec3 m_basisY{ 0.f };
	glm::vec3 m_basisZ{ 0.f };


	float m_nearZ{ 0.1f };
	float m_farZ{ 1000.f };

	float m_aspect{ 0.f };

	GLFWwindow* m_window{ nullptr };

public:


	void Update(float dt);
	void Render(UINT sid);





};

