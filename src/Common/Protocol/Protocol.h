#pragma once

enum class EMessageId : unsigned __int16
{
	None,
	PKT_S2C_SPAWN,
	PKT_S2C_DESPAWN,

	PKT_C2S_MOVE,
	PKT_S2C_MOVE,

	PKT_C2S_TOGGLE_WALKABLE,
	PKT_S2C_TOGGLE_WALKABLE,
};

struct S2C_SPAWN
{
	int ObjectId;
	int X;
	int Y;
};

struct S2C_DESPAWN
{
	int ObjectId;
};

struct C2S_MOVE
{
	unsigned __int8 Input;
};

struct S2C_MOVE
{
	int ObjectId;
};

struct C2S_TOGGLE_WALKABLE
{
	int GridX;
	int GridY;
};

struct S2C_TOGGLE_WALKABLE
{
	int GridX;
	int GridY;
	bool IsWalkable;
};