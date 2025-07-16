#include "World.h"

World::World() : mWindow(nullptr), mRenderer(nullptr), mIsRunning(false)
{
}

World::~World()
{
}

bool World::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Movement Sync",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1000, 1000,
		SDL_WINDOW_SHOWN
	);

	if (!mWindow)
	{
		return false;
	}

	mRenderer = SDL_CreateRenderer(
		mWindow,
		-1,
		SDL_RENDERER_ACCELERATED
	);

	if (!mRenderer)
	{
		return false;
	}

	mIsRunning = true;
	return true;
}

void World::Destroy()
{
	if (mRenderer)
	{
		SDL_DestroyRenderer(mRenderer);
		mRenderer = nullptr;
	}

	if (mWindow)
	{
		SDL_DestroyWindow(mWindow);
		mWindow = nullptr;
	}

	SDL_Quit();
}

void World::Run()
{
	while (mIsRunning)
	{
		HandleEvents();
		Update();
		Render();

		SDL_Delay(16);
	}
}

void World::HandleEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;

		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				mIsRunning = false;
				break;
			}
			break;

		default:
			break;
		}
	}
}

void World::Update()
{
}

void World::Render()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

	// Entity 그리기
	SDL_SetRenderDrawColor(mRenderer, 255, 0, 0, 255);
	SDL_FRect entity = { 5, 5, 20, 20 };
	SDL_RenderFillRectF(mRenderer, &entity);

	// 그리드 그리기
	

	SDL_RenderPresent(mRenderer);
}
