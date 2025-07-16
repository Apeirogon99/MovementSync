#pragma once
#include <SDL.h>

#include "map"

#include "Common/Game/Entity.h"
#include "Common/AStar/PathFinding.h"

class World
{
public:
	World();
	~World();

public:
	bool Initialize();
	void Destroy();
	
public:
	void Run();

private:
	void HandleEvents();
	void Update();
	void Render();

private:
	bool mIsRunning;
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

private:
	PathFinding mPathFinder;
	std::map<int, Entity*> mEntitys;
};