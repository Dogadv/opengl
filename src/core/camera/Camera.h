#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

enum class CameraProjection
{
	Orthographic,
	Perspective // TODO: to be implemented in the future
};

class Camera
{
public:
	Camera(CameraProjection projectionType, float width, float height);
	~Camera();

	void moveBy(glm::vec3 delta);
	void setPosition(glm::vec3 destination);

	void zoomBy(float delta);
	void setZoom(float zoom);

	void rotateBy(glm::vec3 delta);
	void setDirection(glm::vec3 direction);

	inline const glm::mat4 getProjection() const { return m_projection; }
	inline const glm::vec3 getCameraPosition() const { return m_cameraPosition; }
	inline const glm::vec3 getDirection() const { return m_direction; }

	inline const float getZoom() const { return m_zoom; }

	inline const CameraProjection getProjectionType() const { m_projectionType; }

private:
	const CameraProjection m_projectionType;

	float m_zoom;

	glm::mat4 m_projection;

	glm::vec3 m_direction;
	glm::vec3 m_cameraPosition;
};