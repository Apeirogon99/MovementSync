#include "Common/AStar/Grid.h"
#include "Common/Math/Vector2f.h"
#include <cmath>
#include <algorithm>

Grid::Grid() : mNumberOfGrids({100.0f, 100.0f}), mNodeSize(10.0f), mNodeHalfSize(mNodeSize * 0.5f)
{
	mGridSizeX = static_cast<int>(lround(mNumberOfGrids.x / mNodeSize));
	mGridSizeY = static_cast<int>(lround(mNumberOfGrids.y / mNodeSize));

	for (int y = 0; y < mGridSizeY; ++y)
	{
		for (int x = 0; x < mGridSizeX; ++x)
		{
			Vector2f nodePosition = Vector2f(x * mNodeSize + mNodeHalfSize, y * mNodeSize + mNodeHalfSize);
			mGrid[y][x] = new Node(true, nodePosition, x, y);
		}
	}
}

Grid::~Grid()
{
	for (int x = 0; x < mGrid.size(); ++x)
	{
		for (int y = 0; y < mGrid[0].size(); ++y)
		{
			if (mGrid[x][y] != nullptr)
			{
				delete mGrid[x][y];
				mGrid[x][y] = nullptr;
			}
		}
	}
}

std::list<Node*> Grid::GetNeighbours(Node* TargetNode)
{
	std::list<Node*> neighbours;
	for (int x = -1; x <= 1; ++x)
	{
		for (int y = -1; y <= 1; ++y)
		{
			if (x == 0 && y == 0)
			{
				continue;
			}

			int checkX = TargetNode->mGridX + x;
			int checkY = TargetNode->mGridY + y;

			if (checkX >= 0 && checkX < mGridSizeX && checkY >= 0 && checkY < mGridSizeY)
			{
				neighbours.push_back(mGrid[checkX][checkY]);
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
	return mGrid[x][y];
}
