#include "ParticleHandler.h"
#include <iostream>


ParticleHandler::ParticleHandler(float cellSize, float winWidth, float winHeight)
	:
	cellSize(cellSize),
	winWidth(winWidth),
	winHeight(winHeight)
{
	rng.Init();
	int numCol = std::ceil(winWidth / cellSize);
	int numRow = std::ceil(winHeight / cellSize);
	grid.resize(numRow);
	for (auto& col : grid)
		col.resize(numCol);

	NDgrid.resize(numRow);
	for (auto& col : NDgrid)
		col.resize(numCol);

	NDgrid2.resize(numRow);
	for (auto& col : NDgrid2)
		col.resize(numCol);
}

void ParticleHandler::NaiveCollision(ParticleSystem& ps1, ParticleSystem& ps2, ParticleSystem& ps3)
{

	for (auto& p1 : ps1.particlePool)
	{
		if (!p1.active) continue;
		for (auto& p2 : ps2.particlePool)
		{
			if (!p2.active) continue;
			glm::vec2 p1Center = p1.position + glm::vec2((p1.size / 2), (p1.size / 2));
			glm::vec2 p2Center = p2.position + glm::vec2((p2.size / 2), (p2.size / 2));
			float p1R = (p1.size) / 2;
			float p2R = (p2.size) / 2;
			if (glm::distance(p1Center, p2Center) <= p1R + p2R)
			{
				glm::vec2 Position = p2.position;
				glm::vec2 Velocity = glm::vec2(rng.Float(-0.05f, 0.05f), rng.Float(0.1f, 0.2f));
				glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);
				float Size = rng.Float(0.01f, 0.03f);
				ps3.Emit({ Position, Velocity, Color, Size, rng.Float(1.0f, 3.0f) });
				p1.lifeRemaining = 0.0f;
				p2.lifeRemaining = 0.0f;
			}
		}
	}		
}
void ParticleHandler::NaiveCollision(ParticleSystem& ps1, ParticleSystem& ps2)
{

	for (auto& p1 : ps1.particlePool)
	{
		if (!p1.active) continue;
		for (auto& p2 : ps2.particlePool)
		{
			if (!p2.active) continue;
			glm::vec2 p1Center = p1.position + glm::vec2((p1.size / 2), (p1.size / 2));
			glm::vec2 p2Center = p2.position + glm::vec2((p2.size / 2), (p2.size / 2));
			float p1R = (p1.size) / 2;
			float p2R = (p2.size) / 2;
			if (glm::distance(p1Center, p2Center) <= p1R + p2R)
			{
				p1.lifeRemaining = 0.0f;
				p2.lifeRemaining = 0.0f;
				//do interaction;
			}
		}
	}
}


void ParticleHandler::UGCollision(ParticleSystem& ps1, ParticleSystem& ps2)
{
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[0].size() - 1; col++)
		{
			// Check collisions
			for (int i = 0; i < grid[row][col].size(); i++)	
			{
				for (int j = i + 1; j < grid[row][col].size(); j++)
				{
					ParticleSystem::Particle* p1 = grid[row][col][i];
					ParticleSystem::Particle* p2 = grid[row][col][j];
					if (p1->parrentSystem != p2->parrentSystem)
					{
						glm::vec2 p1Center = p1->position + glm::vec2((p1->size / 2), (p1->size / 2));
						glm::vec2 p2Center = p2->position + glm::vec2((p2->size / 2), (p2->size / 2));
						float p1R = (p1->size) / 2;
						float p2R = (p2->size) / 2;
						if (glm::distance(p1Center, p2Center) <= p1R + p2R)
						{
							p1->lifeRemaining = 0.0f;
							p2->lifeRemaining = 0.0f;
							//p1->velocity = p1->velocity * -0.5f;
							//p2->velocity = p2->velocity * -0.5f;
							//p1->lifeRemaining -= 0.5f;
							//p2->lifeRemaining -= 10.5f;
							/*p1->lifeRemaining = 0.0f;
							p2->lifeRemaining = 0.0f;*/
							//p1->velocity = -(p1->velocity);
							//p2->velocity = -(p2->velocity);
						}
					}
				}
			}
		}
	}
}

void ParticleHandler::UGCollision(ParticleSystem& ps1, ParticleSystem& ps2, ParticleSystem& ps3)
{
	//std::vector<ParticleSystem*> systems;
	//systems.push_back(&ps1);
	//systems.push_back(&ps2);
	//BuildGrid(systems);
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[0].size() - 1; col++)
		{
			// Check collisions
			for (int i = 0; i < grid[row][col].size(); i++)
			{
				for (int j = i + 1; j < grid[row][col].size(); j++)
				{
					ParticleSystem::Particle* p1 = grid[row][col][i];
					ParticleSystem::Particle* p2 = grid[row][col][j];
					if (p1->parrentSystem != p2->parrentSystem)
					{
						glm::vec2 p1Center = p1->position + glm::vec2((p1->size / 2), (p1->size / 2));
						glm::vec2 p2Center = p2->position + glm::vec2((p2->size / 2), (p2->size / 2));
						float p1R = (p1->size) / 2;
						float p2R = (p2->size) / 2;
						if (glm::distance(p1Center, p2Center) <= p1R + p2R)
						{
							glm::vec2 Position = p2->position;
							glm::vec2 Velocity = glm::vec2(rng.Float(-0.05f, 0.05f), rng.Float(0.1f, 0.2f));
							glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);
							float Size = rng.Float(0.01f, 0.03f);
							ps3.Emit({ Position, Velocity, Color, Size, rng.Float(1.0f, 3.0f) });
							p1->lifeRemaining = 0.0f;
							p2->lifeRemaining = 0.0f;

						}
					}
				}
			}
		}
	}
}

void ParticleHandler::BuildGrid(std::vector<ParticleSystem*>& systems)
{
	//clear the contents
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[0].size(); col++)
		{
			grid[row][col].clear();
		}
	}

	for (auto& ps : systems)
	{
		for (auto& p : ps->particlePool)
		{
			if (!p.active) continue;

			float aspectRatio = winWidth / winHeight;
			//upper left corner in screen space
			float xPosUL = ((p.position.x / aspectRatio + 1.0f) / 2.0f) * winWidth;
			float yPosUL = (((p.position.y + p.size) - 1.0f) / -2.0f) * winHeight;


			//bottom right corner in screen space
			float xPosBR = (((p.position.x + p.size) / aspectRatio + 1.0f) / 2.0f) * winWidth;
			float yPosBR = ((p.position.y - 1.0f) / -2.0f) * winHeight;


			int startRow = std::max(0, (int)(yPosUL / cellSize));
			int startCol = std::max(0, (int)(xPosUL / cellSize));
			int endRow = std::min((int)grid.size() - 1, (int)std::ceil(yPosBR / cellSize));
			int endCol = std::min((int)grid[0].size() - 1, (int)std::ceil(xPosBR / cellSize));

			// insert into the grids
			for (int row = startRow; row <= endRow; row++)
			{
				for (int col = startCol; col <= endCol; col++)
				{
					grid[row][col].push_back(&p);
				/*	std::cout << "Particle with pos(" << p.position.x << ", " << p.position.y <<
						") in grid: [" << row << "]" << "[" << col << "]" << std::endl;*/
				}
			}
			
		}
	}	
	//PrintGrid();
}



void ParticleHandler::NDUGCollision(ParticleSystem& ps1, ParticleSystem& ps2)
{
	//recalculate particle grid positions
	for (auto& p : ps1.particlePool)
	{
		if (!p.active) continue;
		//convert particle positions to screen space
		float aspectRatio = winWidth / winHeight;
		float xPosUL = ((p.position.x / aspectRatio + 1.0f) / 2.0f) * winWidth;
		float yPosUL = (((p.position.y + p.size) - 1.0f) / -2.0f) * winHeight;
		//determine which grid cell does particle belong to
		int pRow = std::max(0, (int)(yPosUL / cellSize));
		int pCol = std::max(0, (int)(xPosUL / cellSize));
		//update particle's grid position data
		p.row = std::min((int)NDgrid.size() - 1, pRow);
		p.col = std::min((int)NDgrid[0].size() - 1, pCol);
		//increment the cell's count
		NDgrid[p.row][p.col].p1Count++;
	}
	for (auto& p : ps2.particlePool)
	{
		if (!p.active) continue;
		//convert particle positions to screen space
		float aspectRatio = winWidth / winHeight;
		float xPosUL = ((p.position.x / aspectRatio + 1.0f) / 2.0f) * winWidth;
		float yPosUL = (((p.position.y + p.size) - 1.0f) / -2.0f) * winHeight;
		//determine which grid cell does particle belong to
		int pRow = std::max(0, (int)(yPosUL / cellSize));
		int pCol = std::max(0, (int)(xPosUL / cellSize));
		//update particle's grid position data
		p.row = std::min((int)NDgrid.size() - 1, pRow);
		p.col = std::min((int)NDgrid[0].size() - 1, pCol);
		//increment the cell's count
		NDgrid[p.row][p.col].p2Count++;
	}
	//rng collisions
	for (auto& p : ps1.particlePool)
	{
		if (!p.active) continue;

		//rng if particle should die based on number of particles of opposing system present in the grid cell
		float chanceOfDeath = NDgrid[p.row][p.col].p2Count/(float)std::max(1, (NDgrid[p.row][p.col].p1Count + NDgrid[p.row][p.col].p2Count));
		float roll = rng.Float(0.0f, 1.0f);
		if (roll <= chanceOfDeath)
		{
			p.lifeRemaining = 0.0f;
			//p.active = false;
		}
	}
	for (auto& p : ps2.particlePool)
	{
		if (!p.active) continue;

		//rng if particle should die based on number of particles of opposing system present in the grid cell
		float chanceOfDeath = NDgrid[p.row][p.col].p1Count / (float)std::max(1, (NDgrid[p.row][p.col].p2Count + NDgrid[p.row][p.col].p1Count));
		float roll = rng.Float(0.0f, 1.0f);
		if (roll <= chanceOfDeath)
		{
			p.lifeRemaining = 0.0f;
			//p.active = false;
		}
	}
	//reset grid
	for (int row = 0; row < NDgrid.size(); row++)
	{
		for (int col = 0; col < NDgrid[0].size(); col++)
		{
			NDgrid[row][col].p1Count = 0;
			NDgrid[row][col].p2Count = 0;
		}
	}
}
void ParticleHandler::NDUGCollision2(ParticleSystem& ps1, ParticleSystem& ps2, ParticleSystem& ps3)
{
	//recalculate particle grid positions
	for (auto& p : ps1.particlePool)
	{
		if (!p.active) continue;
		//convert particle positions to screen space
		float aspectRatio = winWidth / winHeight;
		float xPosUL = ((p.position.x / aspectRatio + 1.0f) / 2.0f) * winWidth;
		float yPosUL = (((p.position.y + p.size) - 1.0f) / -2.0f) * winHeight;
		//determine which grid cell does particle belong to
		int pRow = std::max(0, (int)(yPosUL / cellSize));
		int pCol = std::max(0, (int)(xPosUL / cellSize));
		//update particle's grid position data
		p.row = std::min((int)NDgrid.size() - 1, pRow);
		p.col = std::min((int)NDgrid[0].size() - 1, pCol);
		//increment the cell's count
		NDgrid[p.row][p.col].p1Count++;
	}
	for (auto& p : ps2.particlePool)
	{
		if (!p.active) continue;
		//convert particle positions to screen space
		float aspectRatio = winWidth / winHeight;
		float xPosUL = ((p.position.x / aspectRatio + 1.0f) / 2.0f) * winWidth;
		float yPosUL = (((p.position.y + p.size) - 1.0f) / -2.0f) * winHeight;
		//determine which grid cell does particle belong to
		int pRow = std::max(0, (int)(yPosUL / cellSize));
		int pCol = std::max(0, (int)(xPosUL / cellSize));
		//update particle's grid position data
		p.row = std::min((int)NDgrid.size() - 1, pRow);
		p.col = std::min((int)NDgrid[0].size() - 1, pCol);
		//increment the cell's count
		NDgrid[p.row][p.col].p2Count++;
	}
	for (auto& p : ps3.particlePool)
	{
		if (!p.active) continue;
		//convert particle positions to screen space
		float aspectRatio = winWidth / winHeight;
		float xPosUL = ((p.position.x / aspectRatio + 1.0f) / 2.0f) * winWidth;
		float yPosUL = (((p.position.y + p.size) - 1.0f) / -2.0f) * winHeight;
		//determine which grid cell does particle belong to
		int pRow = std::max(0, (int)(yPosUL / cellSize));
		int pCol = std::max(0, (int)(xPosUL / cellSize));
		//update particle's grid position data
		p.row = std::min((int)NDgrid.size() - 1, pRow);
		p.col = std::min((int)NDgrid[0].size() - 1, pCol);
		//increment the cell's count
		NDgrid[p.row][p.col].p3Count++;
	}
	//rng collisions
	for (auto& p : ps1.particlePool)
	{
		if (!p.active) continue;

		//rng if particle should die based on number of particles of opposing system present in the grid cell
		float chanceOfDeath = NDgrid[p.row][p.col].p2Count / (float)std::max(1, (NDgrid[p.row][p.col].p1Count + NDgrid[p.row][p.col].p2Count));
		float roll = rng.Float(0.0f, 1.0f);
		if (roll <= chanceOfDeath)
		{
			p.lifeRemaining = 0.0f;
			//p.active = false;
		}
	}
	for (auto& p : ps2.particlePool)
	{
		if (!p.active) continue;

		//rng if particle should die based on number of particles of opposing system present in the grid cell
		float chanceOfDeath = NDgrid[p.row][p.col].p1Count / (float)std::max(1, (NDgrid[p.row][p.col].p2Count + NDgrid[p.row][p.col].p1Count));
		float roll = rng.Float(0.0f, 1.0f);
		if (roll <= chanceOfDeath)
		{
			p.lifeRemaining = 0.0f;
			//p.active = false;
		}
	}
	for (auto& p : ps3.particlePool)
	{
		if (!p.active) continue;

		//rng if particle should die based on number of particles of opposing system present in the grid cell
		float chanceOfDeath = NDgrid[p.row][p.col].p1Count / (float)std::max(1, (NDgrid[p.row][p.col].p2Count + NDgrid[p.row][p.col].p1Count));
		float roll = rng.Float(0.0f, 1.0f);
		if (roll <= chanceOfDeath)
		{
			p.lifeRemaining = 0.0f;
			//p.active = false;
		}
	}
	//reset grid
	for (int row = 0; row < NDgrid.size(); row++)
	{
		for (int col = 0; col < NDgrid[0].size(); col++)
		{
			NDgrid[row][col].p1Count = 0;
			NDgrid[row][col].p2Count = 0;
		}
	}
}

void ParticleHandler::NDUGCollision(ParticleSystem& ps1, ParticleSystem& ps2, ParticleSystem& p3)
{
	//recalculate particle grid positions
	for (auto& p : ps1.particlePool)
	{
		if (!p.active) continue;
		//convert particle positions to screen space
		float aspectRatio = winWidth / winHeight;
		float xPosUL = ((p.position.x / aspectRatio + 1.0f) / 2.0f) * winWidth;
		float yPosUL = (((p.position.y + p.size) - 1.0f) / -2.0f) * winHeight;
		//determine which grid cell particle belongs to
		int pRow = std::max(0, (int)(yPosUL / cellSize));
		int pCol = std::max(0, (int)(xPosUL / cellSize));
		//update particle's grid position data
		p.row = std::min((int)NDgrid.size() - 1, pRow);
		p.col = std::min((int)NDgrid[0].size() - 1, pCol);
		//increment the cell's count
		NDgrid[p.row][p.col].p1Count++;
	}
	for (auto& p : ps2.particlePool)
	{
		if (!p.active) continue;
		//convert particle positions to screen space
		float aspectRatio = winWidth / winHeight;
		float xPosUL = ((p.position.x / aspectRatio + 1.0f) / 2.0f) * winWidth;
		float yPosUL = (((p.position.y + p.size) - 1.0f) / -2.0f) * winHeight;
		//determine which grid cell does particle belong to
		int pRow = std::max(0, (int)(yPosUL / cellSize));
		int pCol = std::max(0, (int)(xPosUL / cellSize));
		//update particle's grid position data
		p.row = std::min((int)NDgrid.size() - 1, pRow);
		p.col = std::min((int)NDgrid[0].size() - 1, pCol);
		//increment the cell's count
		NDgrid[p.row][p.col].p2Count++;
	}
	//rng collisions
	for (auto& p : ps1.particlePool)
	{
		if (!p.active) continue;

		//rng if particle should die based on number of particles of opposing system present in the grid cell
		float chanceOfDeath = NDgrid[p.row][p.col].p2Count / (float)std::max(1, (NDgrid[p.row][p.col].p1Count + NDgrid[p.row][p.col].p2Count));
		float roll = rng.Float(0.0f, 1.0f);
		if (roll <= chanceOfDeath)
		{
			p.active = false;
			
		}
	}
	for (auto& p : ps2.particlePool)
	{
		if (!p.active) continue;

		//rng if particle should die based on number of particles of opposing system present in the grid cell
		float chanceOfDeath = NDgrid[p.row][p.col].p1Count / (float)std::max(1, (NDgrid[p.row][p.col].p2Count + NDgrid[p.row][p.col].p1Count));
		float roll = rng.Float(0.0f, 1.0f);
		if (roll <= chanceOfDeath)
		{
			p.lifeRemaining -= chanceOfDeath * p.lifetime;
			if (p.lifeRemaining <= 0)
			{
				glm::vec2 Position = p.position;
				glm::vec2 Velocity = glm::vec2(rng.Float(-0.05f, 0.05f), rng.Float(0.1f, 0.2f));
				glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);
				float Size = rng.Float(0.01f, 0.03f);
				p3.Emit({ Position, Velocity, Color, Size, rng.Float(1.0f, 3.0f) });
			}
		}
	}
	//reset grid
	for (int row = 0; row < NDgrid.size(); row++)
	{
		for (int col = 0; col < NDgrid[0].size(); col++)
		{
			NDgrid[row][col].p1Count = 0;
			NDgrid[row][col].p2Count = 0;
		}
	}
}

void ParticleHandler::NDUGCollision2(std::vector<ParticleSystem*>& systems)
{
	//systems[0] - fire
	//systems[1] - rain
	//systems[2] - steam
	//systems[3] - snow

	for (size_t i = 0; i < systems.size(); i++)
	{
		for (auto& p : systems[i]->particlePool)
		{
			if (!p.active) continue;
			//convert particle positions to screen space
			float aspectRatio = winWidth / winHeight;
			float xPosUL = ((p.position.x / aspectRatio + 1.0f) / 2.0f) * winWidth;
			float yPosUL = (((p.position.y + p.size) - 1.0f) / -2.0f) * winHeight;
			//determine which grid cell does particle belong to
			int pRow = std::max(0, (int)(yPosUL / cellSize));
			int pCol = std::max(0, (int)(xPosUL / cellSize));
			//update particle's grid position data
			p.row = std::min((int)NDgrid.size() - 1, pRow);
			p.col = std::min((int)NDgrid[0].size() - 1, pCol);
			//increment the cell's count
			if(i == 0) NDgrid2[p.row][p.col].fireCount++;
			if (i == 1) NDgrid2[p.row][p.col].rainCount++;
			if (i == 2) NDgrid2[p.row][p.col].steamCount++;
			if (i == 3) NDgrid2[p.row][p.col].snowCount++;
		}
	}
	for (size_t i = 0; i < systems.size(); i++)
	{
		for (auto& p : systems[i]->particlePool)
		{
			if (!p.active) continue;


			int fireCount = NDgrid2[p.row][p.col].fireCount;
			int rainCount = NDgrid2[p.row][p.col].rainCount;
			int steamCount = NDgrid2[p.row][p.col].steamCount;
			int snowCount = NDgrid2[p.row][p.col].snowCount;
			int totalCount = fireCount + rainCount + steamCount + snowCount;
			

			if (i == 0) //fire particle system
			{
				float interProb = (float)(rainCount + snowCount) / totalCount;
				float roll = rng.Float(0.0f, 1.0f);
				if (roll <= interProb)
				{
					p.lifeRemaining = 0.0f;
				}
			}
			if (i == 1) //rain particle system
			{
				float interProb = (float)(fireCount) / totalCount;
				float roll = rng.Float(0.0f, 1.0f);
				if (roll <= interProb)
				{
					//p.lifeRemaining -= interProb * 10 * p.lifetime;
					p.lifeRemaining = 0.0f;
					if (p.lifeRemaining <= 0)
					{
						p.lifeRemaining = 0.0f;
						//emit a steam particle
						glm::vec2 Position = p.position;
						glm::vec2 Velocity = glm::vec2(rng.Float(-0.05f, 0.05f), rng.Float(0.1f, 0.2f));
						glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);
						float Size = rng.Float(0.01f, 0.03f);
						systems[2]->Emit({ Position, Velocity, Color, Size, rng.Float(1.0f, 3.0f) });
					}	
				}
			}
			if (i == 2) //steam particle system
			{
				float interProb = (float)(snowCount) / totalCount;
				float roll = rng.Float(0.0f, 1.0f);
				if (roll <= interProb)
				{
					p.lifeRemaining = 0.0f;
					//emit a rain particle
					glm::vec2 Position = p.position;
					glm::vec2 Velocity = glm::vec2(rng.Float(-0.01f, 0.01f), rng.Float(-1.0f, -0.7f));
					glm::vec3 Color = glm::vec3(0.2f, 0.42f, 0.65f);
					float Size = rng.Float(0.005, 0.01);
					systems[1]->Emit({ Position, Velocity, Color, Size, 10.0f });
				}
			}
			
			if (i == 3) //snow particle system
			{
			
				//consider particles in the vertical range of the current cell
				float effectiveCount = fireCount + steamCount/2.0f;
				float effectiveTotal = totalCount;
				for (int r = 1; r <= 4; r++)
				{
					int row = p.row + r;
					if (row > NDgrid2.size() - 1) break;
					for (int s = -4; s <= 4; s++)
					{
						int col = p.col + s;
						if (col < 0 || col > NDgrid2[0].size() - 1) continue;
						effectiveCount += NDgrid2[row][col].fireCount / (r * r); //further cells contribute less
						effectiveCount += NDgrid2[row][col].steamCount / (2.0f * (r*r));
						effectiveTotal += NDgrid2[row][col].fireCount + NDgrid2[row][col].rainCount +
							NDgrid2[row][col].steamCount + NDgrid2[row][col].snowCount;
					}
				}
				


				float interProb = effectiveCount / effectiveTotal;
				float roll = rng.Float(0.0f, 1.0f);
				if (roll <= interProb)
				{
					p.lifeRemaining = 0.0f;
					// emit a rain particle
					glm::vec2 Position = p.position;
					glm::vec2 Velocity = glm::vec2(rng.Float(-0.01f, 0.01f), rng.Float(-1.0f, -0.7f));
					glm::vec3 Color = glm::vec3(0.2f, 0.42f, 0.65f);
					float Size = rng.Float(0.005, 0.01);
					systems[1]->Emit({ Position, Velocity, Color, Size, 10.0f });
				}
			}
		}
	}
	//reset grid
	for (int row = 0; row < NDgrid2.size(); row++)
	{
		for (int col = 0; col < NDgrid2[0].size(); col++)
		{
			NDgrid2[row][col].fireCount = 0;
			NDgrid2[row][col].rainCount = 0;
			NDgrid2[row][col].steamCount = 0;
			NDgrid2[row][col].snowCount = 0;
		}
	}
}





void ParticleHandler::PrintGrid() const
{
	int count = 0;
	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[0].size() - 1; col++)
		{
			count += grid[row][col].size();
		}
	}
	std::cout << "Particles in grid: " << count << std::endl;
}




