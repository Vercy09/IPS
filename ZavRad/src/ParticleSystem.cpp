#include "ParticleSystem.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <iostream>
#include <cmath>




ParticleSystem::ParticleSystem(unsigned int particleCount, const Texture& texture)
	:
	particleCount(particleCount),
	poolIndex(0),
	quadVA(),
	quadVB(sizeof(Vertex) * 4 * particleCount),
	particleShader("res/shaders/particleVert.shader", "res/shaders/particleFrag.shader"),
	particleTexture(texture),
	transformMat(glm::mat4(1.0f))
{
	particlePool.resize(particleCount);

	quadVB.Bind();

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(3);
	layout.Push<float>(1);
	layout.Push<float>(2);
	quadVA.AddBuffer(quadVB, layout);

	quadVA.Unbind();

}



void ParticleSystem::Update(float timeStep)
{
	for (auto& particle : particlePool)
	{
		if (!particle.active)
			continue;
		if (particle.lifeRemaining <= 0 || particle.position.y < -1.0f || particle.position.y > 1.0f || particle.position.x < -Window::aspectRatio || particle.position.x > Window::aspectRatio)
		//if (particle.lifeRemaining <= 0)
		{
			numActive--;
			particle.active = false;			
			continue;
		}

		
		particle.lifeRemaining -= timeStep;
		particle.opacity = particle.lifeRemaining / particle.lifetime;
		particle.position += particle.velocity * timeStep;
	}
}

void ParticleSystem::Update(float timeStep, const glm::vec2& acceleration)
{
	for (auto& particle : particlePool)
	{
		if (!particle.active)
			continue;
		if (particle.lifeRemaining <= 0 || particle.position.y < -1.0f || particle.position.y > 1.0f || particle.position.x < -Window::aspectRatio || particle.position.x > Window::aspectRatio)
		{
			numActive--;
			particle.active = false;
			continue;
		}
		particle.lifeRemaining -= timeStep;
		particle.opacity = particle.lifeRemaining / particle.lifetime;
		particle.velocity += acceleration * timeStep;
		particle.position += particle.velocity * timeStep;
	}
}

void ParticleSystem::OnRender(Camera& camera)
{
	particleShader.Bind();
	particleTexture.Bind();
	particleShader.SetUniformMat4f("u_ViewProj", camera.GetViewProjMatrix());
	particleShader.SetUniformMat4f("u_Transform", transformMat);
	particleShader.SetUniform1i("u_Texture", 0);
	
	std::vector<std::array<Vertex, 4>> batch;
	std::vector<QuadIndices> batchIndices;
	unsigned int i = 0;
	for (auto& particle : particlePool)
	{
		if (!particle.active)
			continue;

		auto quad = CreateQuad(particle.position, particle.color, particle.opacity, particle.size);
		batch.push_back(quad);
		batchIndices.push_back({ i, i + 1, i + 2, i + 2, i + 3, i });
		i += 4;
	}
	quadVA.Bind();
	quadVB.Bind();
	IndexBuffer quadIB((unsigned int*)batchIndices.data(), batchIndices.size() * 6);
	quadIB.Bind();

	
	glBufferSubData(GL_ARRAY_BUFFER, 0, batch.size() * 4 * sizeof(Vertex), batch.data());
	glDrawElements(GL_TRIANGLES, batchIndices.size() * 6, GL_UNSIGNED_INT, nullptr);

	quadIB.Unbind();
}

void ParticleSystem::Emit(const ParticleProps particleProps)
{



	Particle& particle = particlePool[poolIndex];
	if (!particle.active) numActive++;
	particle.active = true;
	particle.position = particleProps.Position;
	particle.velocity = particleProps.Velocity;
	particle.color = particleProps.Color;
	particle.lifetime = particleProps.Lifetime;
	particle.lifeRemaining = particleProps.Lifetime;
	particle.size = particleProps.Size;
	particle.parrentSystem = this;

	poolIndex++;

	poolIndex = poolIndex % particlePool.size();
	
}

void ParticleSystem::SetTransform(const glm::mat4& transMat)
{
	transformMat = transMat;
}

const unsigned int ParticleSystem::GetParticleCount()
{
	return particleCount;
}

std::array<ParticleSystem::Vertex, 4> ParticleSystem::CreateQuad(glm::vec2 position, glm::vec3 color, float opacity, float size)
{
	Vertex v0;
	v0.Position = { position.x, position.y };
	v0.Color = color;
	v0.Opacity = opacity;
	v0.TexCoords = {0.0f, 0.0f};
	//v0.TexID = textureID;
		
	Vertex v1;
	v1.Position = { position.x + size, position.y };
	v1.Color = color;
	v1.Opacity = opacity;
	v1.TexCoords = { 1.0f, 0.0f };
	//v1.TexID = textureID;

	Vertex v2;
	v2.Position = { position.x + size, position.y + size };
	v2.Color = color;
	v2.Opacity = opacity;
	v2.TexCoords = { 1.0f, 1.0f };
	//v2.TexID = textureID;

	Vertex v3;
	v3.Position = { position.x, position.y + size };
	v3.Color = color;
	v3.Opacity = opacity;
	v3.TexCoords = { 0.0f, 1.0f };
	//v3.TexID = textureID;

	return {v0, v1, v2, v3};
}



