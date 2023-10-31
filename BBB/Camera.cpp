#include "pch.h"
#include "Camera.h"

Camera::Camera(GLFWwindow* Window, UINT ShaderId, glm::vec3 EYE, float NearZ, float FarZ)
	: m_window(Window), m_shaderId(ShaderId), m_eye(EYE), m_nearZ(NearZ), m_farZ(FarZ)
{
	int w, h;

	glfwGetFramebufferSize(m_window, &w, &h);

	m_aspect = static_cast<float>(w) / static_cast<float>(h);


	m_projectionLocation = glGetUniformLocation(m_shaderId, "perspective");
	m_lookatLocation = glGetUniformLocation(m_shaderId, "lookat");
}

void Camera::Update(){

	int w, h;
	glfwGetWindowSize(m_window, &w, &h);
	m_aspect = static_cast<float>(w) / static_cast<float>(h);

	



}

void Camera::Render(UINT sid){


	glUniformMatrix4fv(m_projectionLocation, 1, GL_FALSE, glm::value_ptr(
		glm::perspective(glm::radians(m_fovY), m_aspect, m_nearZ, m_farZ))
	);


	glUniformMatrix4fv(m_lookatLocation, 1, GL_FALSE, glm::value_ptr(
		glm::lookAt(m_eye, m_at + m_eye, m_up))
	);




}
