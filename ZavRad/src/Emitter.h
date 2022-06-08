#pragma once
#include "ParticleSystem.h"
#include "Random.h"


class Emitter
{
public:
	Emitter(ParticleSystem& ps);
	void SimulateFire(const glm::vec2& location, float rate, float timeStep);
	void SimulateRain(const glm::vec2& range, float rate, float timeStep);
	void SimulateSnow(const glm::vec2& range, float rate, float timeStep);
	void RandomEmissions(const glm::vec3& color, float rate, float timeStep);
private:
	Random rng;
	ParticleSystem& ps;
	float emitCount;
};