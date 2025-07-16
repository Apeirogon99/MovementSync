#pragma once
#include "Common/Math/Vector2f.h"

class Node
{
public:
	Node(bool Walkable, const Vector2f& Position, int GridX, int GridY);
	~Node();

private:
	Node() = delete;

public:
	bool operator==(const Node& OtherNode)
	{
		return (GetTotalCost() == OtherNode.GetTotalCost());
	}

public:
	inline int	GetTotalCost()		const { return mActualCost + mHeuristicCost; }

public:
	bool mIsWalkable;
	
	Vector2f mPosition;
	int mGridX;
	int mGridY;

	int mActualCost;
	int mHeuristicCost;

	Node* mParent;
};