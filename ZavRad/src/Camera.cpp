#include "Camera.h"

Camera::Camera(float left, float right, float bottom, float top)
	:
	projectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
	viewMatrix(1.0f)
{
	viewProjMatrix = projectionMatrix * viewMatrix;
}

void Camera::SetPosition(const glm::vec3& pos)
{
	position = pos;
	viewMatrix = glm::translate(viewMatrix, position);
	viewProjMatrix = projectionMatrix * viewMatrix;
}

void Camera::SetRotation(float radians)
{
	rotation = radians;
	viewMatrix = glm::rotate(viewMatrix, glm::radians(radians), glm::vec3(0, 0, 1));
	viewProjMatrix = projectionMatrix * viewMatrix;
}

const glm::vec3& Camera::GetPosition() const
{
	return position;
}

const float Camera::GetRotation() const
{
	return rotation;
}

const glm::mat4& Camera::GetProjectionMatrix() const
{
	return projectionMatrix;
}

const glm::mat4& Camera::GetViewMatrix() const
{
	return viewMatrix;
}

const glm::mat4& Camera::GetViewProjMatrix() const
{
	return viewProjMatrix;
}

void Camera::SetViewMatrix(const glm::mat4& viewMat)
{
	viewMatrix = viewMat;
	viewProjMatrix = projectionMatrix * viewMatrix;
}

void Camera::SetProjMatrix(const glm::mat4& projMat)
{
	projectionMatrix = projMat;
	viewProjMatrix = projectionMatrix * viewMatrix;
}

