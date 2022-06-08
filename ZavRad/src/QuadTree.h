#pragma once
#include "glm/glm.hpp"
#include <vector>
#include "ParticleSystem.h"

struct Boundary
{
	glm::vec2 topLeft;
	glm::vec2 botRight;
};



class QuadTree
{
public:
	QuadTree(Boundary boundary, unsigned int capacity);
	void Insert(ParticleSystem::Particle& p);
private:
	void Subdivide();
private:
	struct Node
	{
		Boundary boundary;
		std::vector<ParticleSystem::Particle*> particles;
	};
private:
	Boundary boundary;
	unsigned int capacity;
	QuadTree* topLeftQT;
	QuadTree* topRightQT;
	QuadTree* botLeftQT;
	QuadTree* botRightQT;
};