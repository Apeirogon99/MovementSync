#pragma once
#include "Common/AStar/Node.h"
#include "Common/Math/Vector2f.h"
#include "memory"
#include "vector"
#include "list"

class Grid
{
public:
	Grid(const Vector2f& GridSize, float NodeSize);
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
	std::vector<std::vector<std::unique_ptr<Node>>> mGrid;

	Vector2f mNumberOfGrids;
	float	mNodeSize;
	float	mNodeHalfSize;
	int		mGridSizeX;
	int		mGridSizeY;
};

