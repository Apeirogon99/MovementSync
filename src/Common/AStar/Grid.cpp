#include "Common/AStar/Grid.h"
#include <cmath>
#include <algorithm>

Grid::Grid(const Vector2f& GridSize, float NodeSize) : mNumberOfGrids(GridSize), mNodeSize(NodeSize), mNodeHalfSize(NodeSize * 0.5f)
{
	mGridSizeX = static_cast<int>(lround(mNumberOfGrids.x / mNodeSize));
	mGridSizeY = static_cast<int>(lround(mNumberOfGrids.y / mNodeSize));

	mGrid.resize(mGridSizeY);
	for (int y = 0; y < mGridSizeY; ++y)
	{
		mGrid[y].resize(mGridSizeX);
		for (int x = 0; x < mGridSizeX; ++x)
		{
			Vector2f nodePosition = Vector2f(x * mNodeSize + mNodeHalfSize, y * mNodeSize + mNodeHalfSize);
			mGrid[y][x] = std::make_unique<Node>(true, nodePosition, x, y);
		}
	}
}

Grid::~Grid()
{
	for (int x = 0; x < mGrid.size(); ++x)
	{
		for (int y = 0; y < mGrid[0].size(); ++y)
		{
			if (mGrid[y][x] != nullptr)
			{		  
				mGrid[y][x].reset();
				mGrid[y][x] = nullptr;
			}
		}
	}
}

std::list<Node*> Grid::GetNeighbours(Node* TargetNode)
{
	std::list<Node*> neighbours;
	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			if (x == 0 && y == 0)
			{
				continue;
			}

			int checkX = TargetNode->mGridX + x;
			int checkY = TargetNode->mGridY + y;

			if (checkX >= 0 && checkX < mGridSizeX && checkY >= 0 && checkY < mGridSizeY)
			{
				neighbours.push_back(mGrid[checkY][checkX].get());
			}
		}
	}
	return neighbours;
}

Node* Grid::GetNodeFromPosition(Vector2f Position)
{
	float percentX = Position.x / mNumberOfGrids.x;
	float percentY = Position.y / mNumberOfGrids.y;
	percentX = std::clamp(percentX, 0.0f, 1.0f);
	percentY = std::clamp(percentY, 0.0f, 1.0f);

	int x = static_cast<int>(lround((mGridSizeX - 1) * percentX));
	int y = static_cast<int>(lround((mGridSizeY - 1) * percentY));
	return mGrid[y][x].get();
}
