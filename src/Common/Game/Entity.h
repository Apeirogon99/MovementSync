#pragma once
#include "Common/Math/Vector2f.h"
#include "Common/AStar/Node.h"
#include "list"

class Entity
{
public:
	Entity(const Vector2f& Position);

public:
	void MoveTowardsNextPath(float DeltaTime);

public:
	Vector2f mPosition;
	Vector2f mVelocity;
	float mMoveSpeed;

	std::list<Node*> mPath;
};
