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
	inline bool IsRunning() const { return mIsRunning; }

public:
	void UpdateTime();
	void HandleEvents();
	void Update();
	void Render();
	void LimitFrameRate();

private:
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;

public:
	bool mIsRunning;
	uint64_t mFrequency;
	uint64_t mLastTime;

	std::map<uint32_t, std::unique_ptr<Entity>> mEntitys;
	uint32_t mLocalEntityId;

	std::unique_ptr<PathFinding> mPathFinder;
	std::unique_ptr<Grid> mMap;
};