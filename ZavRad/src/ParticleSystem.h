#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>
#include "VertexArray.h"
#include "Shader.h"
#include "Camera.h"
#include <array>
#include <Texture.h>
#include "globals.h"



struct ParticleProps
{
	glm::vec2 Position;
	glm::vec2 Velocity;
	glm::vec3 Color;
	float Size;
	float Lifetime = 10.0f;
};

class ParticleSystem
{
public:
	ParticleSystem(unsigned int particleCount, const Texture& texture);
	void Update(float timeStep);
	void Update(float timeStep, const glm::vec2& acceleration);
	void OnRender(Camera& camera);
	void Emit(const ParticleProps particleProps);
	void SetTransform(const glm::mat4& transMat);
	const unsigned int GetParticleCount();
	friend class ParticleHandler;
	friend class Emitter;
public:
	struct Particle 
	{
		glm::vec2 position;
		glm::vec2 velocity;
		glm::vec3 color;
		float opacity = 1.0f;
		float size;
		float lifetime = 1.0f;
		float lifeRemaining = 1.0f;
		bool active = false;
		ParticleSystem* parrentSystem;

		int row;
		int col;
	};
	unsigned int numActive;
private:
	struct Vertex
	{
		glm::vec2 Position;
		glm::vec3 Color;
		float Opacity;
		glm::vec2 TexCoords;
		//float TexID;
	};
	struct QuadIndices 
	{
		unsigned int i0, i1, i2;
		unsigned int i3, i4, i5;
	};
	static std::array<Vertex, 4> CreateQuad(glm::vec2 position, glm::vec3 color, float opacity, float size);
private:
	std::vector<Particle> particlePool;
	size_t poolIndex;
	unsigned int particleCount;
	VertexArray quadVA;
	VertexBuffer quadVB;
	Shader particleShader;
	Texture particleTexture;
	glm::mat4 transformMat;
	
};

