#include "Common/Game/Entity.h"

Entity::Entity(const Vector2f& Position) : mPosition(Position), mVelocity(), mMoveSpeed(100.0f)
{
}

void Entity::MoveTowardsNextPath(float DeltaTime)
{
	if (mPath.size() <= 0) return;

	Node* node = mPath.front();
	Vector2f nodePosition = node->mPosition;

	Vector2f direction = nodePosition - mPosition;
	float distance = direction.magnitude();
	if (distance <= 1.0f)
	{
		mPath.pop_front();
	}

	Vector2f unitDirection = direction.normalized();
	mVelocity = unitDirection * mMoveSpeed * DeltaTime;

	mPosition += mVelocity;
}
