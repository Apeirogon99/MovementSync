#pragma once
#include "Common/AStar/Node.h"
#include "array"
#include "list"

class Grid
{
public:
	Grid();
	~Grid();

private:
	Grid(const Grid&) = delete;
	Grid operator=(const Grid&) = delete;

	Grid(Grid&&) = delete;
	Grid operator=(Grid&&) = delete;

public:
	std::list<Node*> GetNeighbours(Node* TargetNode);
	Node* GetNodeFromPosition(Vector2f Position);

public:
	std::array<std::array<Node*, 10>, 10> mGrid = { nullptr, };

	Vector2f mNumberOfGrids;
	float	mNodeSize;
	float	mNodeHalfSize;
	int		mGridSizeX;
	int		mGridSizeY;
};

