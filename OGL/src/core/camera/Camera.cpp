#include "Camera.h"

Camera::Camera(CameraProjection projectionType, float width, float height)
	: m_projectionType(projectionType),
	m_cameraPosition(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_direction(glm::vec3(0.0f, 0.0f, 0.0f)),
	m_zoom(1.0f)
{
	m_projection = glm::ortho(.0f, width, .0f, height);
}

Camera::~Camera()
{
}

void Camera::moveBy(glm::vec3 delta)
{
	m_cameraPosition += delta;
}

void Camera::setPosition(glm::vec3 destination)
{
	m_cameraPosition = destination;
}

void Camera::zoomBy(float delta)
{
	m_zoom += delta;
}

void Camera::setZoom(float zoom)
{
	m_zoom = zoom;
}

void Camera::rotateBy(glm::vec3 delta)
{
	// TODO: implement
	__debugbreak();
}

void Camera::setDirection(glm::vec3 direction)
{
	// TODO: implement
	__debugbreak();
}
