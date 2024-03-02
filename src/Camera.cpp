//-----------------------------------------------------------------------------
// File:			Camera.cpp
// Original Author:	Ryan Campbell
//
// class to represent a camera to move around the world
//-----------------------------------------------------------------------------
#include "Camera.hpp"

// constructor
Camera::Camera(int width, int height, wolf::App* pApp)
	: m_camFront(glm::vec3(0.0f, 0.0f, -1.0f))
	, m_width(width)
	, m_height(height)
	, m_pApp(pApp)
	, m_upDirection(WORLD_UP)
	, m_rightDirection(glm::vec3(0.0f, 0.0f, 1.0f))
	, m_yaw(-90.0f)
	, m_pitch(0.0f)
	, m_cameraSens(0.1f)
	, m_position(glm::vec3(0.0f, 5.0f, 30.0f))
	, m_mProj(glm::mat4(1.0f))
	, m_mView(glm::mat4(1.0f))
	, m_velocity(10.0f)
{
	glfwSetInputMode(m_pApp->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

Camera::~Camera()
{
}

// screen center
float lastXPos = 640.0f;
float lastYPos = 360.0f;
bool shiftIsUp = true;
void Camera::update(float dt)
{
	// get scrollwheel input
	auto mouseScroll = m_pApp->getMouseScroll().y;
	m_velocity = std::max(m_velocity + mouseScroll, 0.1f);

	updateCamAxisVectors();

	bool isSlowCamera = m_pApp->isKeyDown(GLFW_KEY_LEFT_SHIFT);
	float camMovement = dt * m_velocity / (isSlowCamera ? 2.0f : 1.0f);

	// get keyboard input
	if (m_pApp->isKeyDown('w')) {
		m_position += m_camFront * camMovement;
	}
	if (m_pApp->isKeyDown('a')) {
		m_position -= glm::normalize(glm::cross(m_camFront, m_upDirection)) * camMovement;
	}
	if (m_pApp->isKeyDown('s')) {
		m_position -= m_camFront * camMovement;
	}
	if (m_pApp->isKeyDown('d')) {
		m_position += glm::normalize(glm::cross(m_camFront, m_upDirection)) * camMovement;
	}
	if (m_pApp->isKeyDown('q')) {
		m_position += glm::normalize(m_upDirection) * camMovement;
	}
	if (m_pApp->isKeyDown('e')) {
		m_position -= glm::normalize(m_upDirection) * camMovement;
	}
	m_mView = glm::lookAt(m_position, m_camFront + m_position, m_upDirection);
	// fov,aspect ratio, near plane, far plane
	m_mProj = glm::perspective(glm::radians(60.0f), (float)m_width / (float)m_height, 0.1f, 500.0f);
}

void Camera::setWidth(int width)
{
	m_width = width;
}

void Camera::setHeight(int height)
{
	m_height = height;
}

// updates the unit vectors the represent the axis of the camera
void Camera::updateCamAxisVectors()
{
	glm::vec2 mousePos = m_pApp->getMousePos();
	float xOffset = mousePos.x - lastXPos;
	float yOffset = lastYPos - mousePos.y;
	lastXPos = mousePos.x;
	lastYPos = mousePos.y;
	xOffset *= m_cameraSens;
	yOffset *= m_cameraSens;

	m_yaw += xOffset;
	m_pitch += yOffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (m_pitch > 89.0f)
		m_pitch = 89.0f;
	if (m_pitch < -89.0f)
		m_pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_camFront = glm::normalize(front);

	m_rightDirection = glm::normalize(glm::cross(m_camFront, WORLD_UP));
	m_upDirection = glm::normalize(glm::cross(m_rightDirection, m_camFront));
}
