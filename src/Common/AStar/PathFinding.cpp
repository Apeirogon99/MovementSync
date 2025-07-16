#include "Common/AStar/PathFinding.h"
#include <cmath>
#include <list>
#include <set>
#include <algorithm>

PathFinding::PathFinding()
{
}

PathFinding::~PathFinding()
{

}

std::list<Node*> PathFinding::FindPath(Vector2f StartPosition, Vector2f TargetPosition)
{
	Node* startNode = mGrid.GetNodeFromPosition(StartPosition);
	Node* targetNode = mGrid.GetNodeFromPosition(TargetPosition);

	std::list<Node*> path;
	std::list<Node*> openSet;
	std::set<Node*> closedSet;

	openSet.push_back(startNode);
	while (openSet.size() > 0)
	{
		// ���� ���� ���� ���� ��带 �����Ѵ�.
		Node* currentNode = *openSet.begin();
		for (auto iter = openSet.begin(); iter != openSet.end(); ++iter)
		{
			Node* node = *iter;
			if (node->GetTotalCost() < currentNode->GetTotalCost() ||
				(node->GetTotalCost() == currentNode->GetTotalCost() &&
					node->mHeuristicCost < currentNode->mHeuristicCost))
			{
				currentNode = node;
			}
		}

		// ���� ���� ���� ���� ��尡 �������� Ž���� �����Ѵ�.
		if (currentNode == targetNode)
		{
			// ��� ����
			while (targetNode != startNode)
			{
				path.push_back(targetNode);
				targetNode = targetNode->mParent;
			}
			path.reverse();
			break;
		}

		// ���� ��带 ���� �¿��� ���� Ŭ����� ������ �̵��Ѵ�.
		openSet.remove(currentNode);
		closedSet.insert(currentNode);

		// �̿���带 �����ͼ� ���� ����� �� ���� �¿� �߰��Ѵ�.
		for(Node* neighbourNode : mGrid.GetNeighbours(currentNode))
		{
			if (!neighbourNode->mIsWalkable || closedSet.contains(neighbourNode))
			{
				continue;
			}

			int g = currentNode->mActualCost + GetDistance(currentNode, neighbourNode);
			int h = GetDistance(neighbourNode, targetNode);
			int f = g + h;

			// ���� �¿� �̹� �ߺ� ��尡 �ִ� ��� ���� ���� ������ �����Ѵ�.
			if (std::find(openSet.begin(), openSet.end(), neighbourNode) == openSet.end())
			{
				neighbourNode->mActualCost = g;
				neighbourNode->mHeuristicCost = h;
				neighbourNode->mParent = currentNode;
				openSet.push_back(neighbourNode);
			}
			else
			{
				if (neighbourNode->GetTotalCost() > f)
				{
					neighbourNode->mActualCost = g;
					neighbourNode->mParent = currentNode;
				}
			}
		}
	}
	return path;
}

//std::list<Node*> PathFinding::RetracePath(Node* StartNode, Node* EndNode)
//{
//	std::list<Node*> path;
//	Node* currentNode = EndNode;
//
//	while (currentNode != StartNode) 
//	{
//		path.push_back(currentNode);
//		currentNode = currentNode->mParent;
//	}
//
//	path.reverse();
//	return path;
//}

int PathFinding::GetDistance(Node* Lhs, Node* Rhs)
{
	int dstX = abs(Lhs->mGridX - Rhs->mGridX);
	int dstY = abs(Lhs->mGridY - Rhs->mGridY);
	
	if (dstX > dstY)
	{
		return 14 * dstY + 10 * (dstX - dstY);
	}
	return 14 * dstX + 10 * (dstY - dstX);
}
