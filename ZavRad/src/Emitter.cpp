#include "Emitter.h"


Emitter::Emitter(ParticleSystem& ps)
	:
	ps(ps),
	emitCount(0.0f)
{
	rng.Init();
}

void Emitter::SimulateFire(const glm::vec2& location, float rate, float timeStep)
{
	emitCount += rate * timeStep;
	for (auto& p : ps.particlePool)
	{
		if (!p.active) continue;
		float lifeProgress = (p.lifeRemaining / p.lifetime);
		p.color.g = lifeProgress * 0.8;
		p.velocity += glm::vec2(-p.velocity.x * (3 - lifeProgress), 0.0f) * timeStep;
	}
	while ((int)emitCount > 0)
	{
		glm::vec2 Position = location + glm::vec2(rng.Float(-0.1f, 0.1f), rng.Float(-0.03f, 0.03f));
		glm::vec2 Velocity = glm::vec2(rng.Float(-0.2f, 0.2f), rng.Float(0.05f, 0.1f));
		glm::vec3 Color = glm::vec3(1.0f, 0.9f, 0.0f);
		float Size = rng.Float(0.01, 0.03);
		ps.Emit({ Position, Velocity, Color, Size, rng.Float(3.0f, 10.0f) });
		emitCount--;
	}
	ps.Update(timeStep);
}

void Emitter::SimulateRain(const glm::vec2& range, float rate, float timeStep)
{
	emitCount += rate * timeStep;
	/*for (auto& p : ps.particlePool)
	{
		if (!p.active) continue;
		p.velocity += glm::vec2(0.0f, -0.5f) * timeStep;
	}*/
	while ((int)emitCount > 0)
	{
		glm::vec2 Position = glm::vec2(rng.Float(range.x, range.y), 1.0f);
		glm::vec2 Velocity = glm::vec2(rng.Float(-0.01f, 0.01f), rng.Float(-1.0f, -0.7f));
		glm::vec3 Color = glm::vec3(0.2f, 0.42f, 0.65f);
		float Size = rng.Float(0.005, 0.01);
		ps.Emit({ Position, Velocity, Color, Size, 10.0f });
		emitCount--;
	}
	ps.Update(timeStep, glm::vec2(0.0f, -0.8f));
}

void Emitter::SimulateSnow(const glm::vec2& range, float rate, float timeStep)
{
	emitCount += rate * timeStep;
	/*for (auto& p : ps.particlePool)
	{
		if (!p.active) continue;
		p.velocity += glm::vec2(0.0f, -0.5f) * timeStep;
	}*/
	while ((int)emitCount > 0)
	{
		glm::vec2 Position = glm::vec2(rng.Float(range.x, range.y), 1.0f);
		glm::vec2 Velocity = glm::vec2(rng.Float(-0.01f, 0.01f), -rng.Float(0.1f, 0.3f));
		glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);
		float Size = rng.Float(0.02, 0.04);
		ps.Emit({ Position, Velocity, Color, Size, 30.0f });
		emitCount--;
	}
	ps.Update(timeStep, glm::vec2(0.0f, -0.01f));
}

void Emitter::RandomEmissions(const glm::vec3& color, float rate, float timeStep)
{
	emitCount += rate * timeStep;
	while ((int)emitCount > 0)
	{
		glm::vec2 Position = glm::vec2(rng.Float(-Window::aspectRatio, Window::aspectRatio), rng.Float(-1.0f, 1.0f));
		glm::vec2 Velocity = glm::vec2(rng.Float(-0.1f, 0.1f), rng.Float(-0.1f, 0.1f));
		glm::vec3 Color = color;
		float Size = rng.Float(0.01, 0.04);
		ps.Emit({ Position, Velocity, Color, Size, 30.0f });
		emitCount--;
	}
}
