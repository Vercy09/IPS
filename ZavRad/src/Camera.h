#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


class Camera
{
public:
	Camera(float left, float right, float bottom, float top);

	void SetPosition(const glm::vec3& pos);
	void SetRotation(float radians);

	const glm::vec3& GetPosition() const;
	const float GetRotation() const;

	const glm::mat4& GetProjectionMatrix() const;
	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetViewProjMatrix() const;
	void SetViewMatrix(const glm::mat4& viewMat);
	void SetProjMatrix(const glm::mat4& projMat);
private:
	glm::vec3 position;
	float rotation;
	glm::mat4 projectionMatrix;
	glm::mat4 viewMatrix;
	glm::mat4 viewProjMatrix;
};

