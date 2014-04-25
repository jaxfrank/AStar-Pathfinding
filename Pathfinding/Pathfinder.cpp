/*The MIT License (MIT)
*
*Copyright (c) 2014 Frank McCoy
*
*Permission is hereby granted, free of charge, to any person obtaining a copy
*of this software and associated documentation files (the "Software"), to deal
*in the Software without restriction, including without limitation the rights
*to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*copies of the Software, and to permit persons to whom the Software is
*furnished to do so, subject to the following conditions:
*
*The above copyright notice and this permission notice shall be included in all
*copies or substantial portions of the Software.
*
*THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*SOFTWARE.
*/
#include "Pathfinder.h"
#include "nodeMap.h"
#include "Vector2i.h"
#include "PathNode.h"
#include "Path.h"

#include <set>
#include <map>
#include <iostream>


Pathfinding::Pathfinder::Pathfinder(void) {}


Pathfinding::Pathfinder::~Pathfinder(void) {}

void Pathfinding::Pathfinder::findPath(NodeMap* nodeMap, Vector2i start, Vector2i end) {
	if(!nodeMap->contains(start) || !nodeMap->contains(end)) return;
	std::multimap<int, PathNode*> openList;
	std::multiset<PathNode*, PathNode::CompareLessPtr> closedList;
	PathNode* endNode = nodeMap->getNode(end);
	endNode->h_heuristic = 0; 
	endNode->calcF();

	PathNode* startNode = nodeMap->getNode(start);
	startNode->h_heuristic = calcH(start, start, end); 
	startNode->calcF();
	startNode->inOpenList = true;
	openList.insert(std::pair<int, PathNode*>(startNode->f_total, startNode));
	while(!endNode->inClosedList) {
		if(openList.empty()) return; // No path to end point
		std::multimap<int, PathNode*>::iterator currentNodeIt = openList.lower_bound(-30000);
		PathNode* currentNode = currentNodeIt->second;
		currentNode->inClosedList = true;
		openList.erase(currentNodeIt);
		closedList.insert(currentNode);

		PathNode** surroundingNodes = nodeMap->getSurroundingNodes(currentNode->position);
		if(surroundingNodes == NULL) return; // This should never happen
		for(int i = 0; i < nodeMap->numSurroundingNodes(); i++) {
			PathNode* neighbor = surroundingNodes[i];
			if(neighbor == NULL || neighbor == currentNode) continue;
			neighbor->h_heuristic = calcH(neighbor->position, start, end);
			neighbor->calcF();
			if(!neighbor->inClosedList) {
				if(!neighbor->inOpenList){
					neighbor->parent = currentNode;
					neighbor->g_movementCost = currentNode->g_movementCost + currentNode->cost;
					neighbor->calcF();
					neighbor->inOpenList = true;
					openList.insert(std::pair<int, PathNode*>(neighbor->f_total, neighbor));

				} else {
					if(currentNode->g_movementCost > (neighbor->g_movementCost + neighbor->cost)) {
						currentNode->parent = neighbor;
						currentNode->g_movementCost = neighbor->g_movementCost + currentNode->cost;
						currentNode->calcF();
					}
				}
			}
		}
	}
}

int Pathfinding::Pathfinder::calcH(const Vector2i start, const Vector2i begin, const Vector2i end) const {
	int dx1 = start.x - end.x;
	int dy1 = start.x - end.y;
	int dx2 = begin.x - end.x;
	int dy2 = begin.y - end.y;
	int cross = abs(dx1 * dy2 - dx2 * dy1);
	return abs(start.x - end.x) + abs(start.y - end.y) + cross;
	/*int dx1 = point.X - endPoint.X
    'Dim dy1 = point.Y - endPoint.Y
    'Dim dx2 = startPoint.X - endPoint.X
    'Dim dy2 = startPoint.Y - endPoint.Y
    'Dim cross = Math.Abs(dx1 * dy2 - dx2 * dy1)
    'Return CInt(standardMovementCost * (Math.Abs(point.X - endPoint.X) + Math.Abs(point.Y - endPoint.Y)) + (cross))
	*/
	//return pow(abs(end.x - start.x) + abs(end.y - start.y), 2);
}