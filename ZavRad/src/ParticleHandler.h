#pragma once
#include "ParticleSystem.h"
#include "glm/glm.hpp"
#include "Random.h"
#include <vector>

class ParticleHandler
{
public:
	ParticleHandler(float cellSize, float winWidth, float winHeight);
	void NaiveCollision(ParticleSystem& ps1, ParticleSystem& ps2, ParticleSystem& ps3);
	void NaiveCollision(ParticleSystem& ps1, ParticleSystem& ps2);
	void UGCollision(ParticleSystem& ps1, ParticleSystem& ps2);
	void UGCollision(ParticleSystem& ps1, ParticleSystem& ps2, ParticleSystem& ps3);
	void BuildGrid(std::vector<ParticleSystem*>& systems);
	void NDUGCollision(ParticleSystem& ps1, ParticleSystem& ps2);
	void NDUGCollision2(ParticleSystem& ps1, ParticleSystem& ps2, ParticleSystem& ps3);
	void NDUGCollision(ParticleSystem& ps1, ParticleSystem& ps2, ParticleSystem& p3);
	void NDUGCollision2(std::vector<ParticleSystem*>& systems);
private:
	void PrintGrid() const;
private:
	struct GridCount
	{
		int p1Count = 0;
		int p2Count = 0;
		int p3Count = 0;
	};
	struct CellData
	{
		int fireCount = 0;
		int rainCount = 0;
		int steamCount = 0;
		int snowCount = 0;
	};
private:
	std::vector<std::vector<std::vector<ParticleSystem::Particle*>>> grid;
	std::vector<std::vector<GridCount>> NDgrid;
	std::vector<std::vector<CellData>> NDgrid2;
	float cellSize;
	float winWidth;
	float winHeight;
	Random rng;
};