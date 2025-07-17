#include "ClientMessageHandler.h"

void Handle_INVALID(uint16_t Id, uint16_t Size, const std::vector<BYTE>& Data)
{
}

void Handle_S2C_MOVE(const std::unique_ptr<World>& World, const S2C_MOVE* Protocol)
{
}

void Handle_S2C_TOGGLE_WALKABLE(const std::unique_ptr<World>& World, const S2C_TOGGLE_WALKABLE* Protocol)
{
	World->mMap->mGrid[Protocol->GridY][Protocol->GridX]->mIsWalkable = Protocol->IsWalkable;
}
