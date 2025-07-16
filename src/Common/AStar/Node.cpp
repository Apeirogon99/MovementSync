#include "Common/AStar/Node.h"

Node::Node(bool Walkable, const Vector2f& Position, int GridX, int GridY)
	: mIsWalkable(Walkable), mPosition(Position), mGridX(GridX), mGridY(GridY), mActualCost(0), mHeuristicCost(0), mParent(nullptr)
{
}

Node::~Node()
{
	mParent = nullptr;
}
