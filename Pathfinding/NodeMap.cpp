#include "NodeMap.h"
#include "PathNode.h"

Pathfinding::NodeMap::NodeMap(int width, int height): 
	width(width), 
	height(height) 
{
	nodes.resize(width);
	for(int i = 0; i < width; i++) {
		nodes[i].resize(height);
	}

	for(int i = 0; i < width; i++ ) {
		for(int j = 0; j < height;  j++) {
			getNode(i, j)->position = Vector2i(i,j);
		}
	}

}

Pathfinding::PathNode** Pathfinding::NodeMap::getSurroundingNodes(const Pathfinding::Vector2i position) {
	if(outsideBounds(position.x, position.y))  return NULL;
	PathNode** sourroundingNodes = NULL; //Array of pointers to PathNodes
	switch (moveableDirections) {
	case FOUR:
		sourroundingNodes = new PathNode*[4];

		sourroundingNodes[0] = getNode(position.x, position.y + 1);
		sourroundingNodes[1] = getNode(position.x + 1, position.y);
		sourroundingNodes[2] = getNode(position.x, position.y - 1);
		sourroundingNodes[3] = getNode(position.x - 1, position.y);

		break;
	case EIGHT:
		sourroundingNodes = new PathNode*[8];

		sourroundingNodes[0] = getNode(position.x    , position.y + 1);
		sourroundingNodes[1] = getNode(position.x + 1, position.y + 1);
		sourroundingNodes[2] = getNode(position.x + 1, position.y    );
		sourroundingNodes[3] = getNode(position.x + 1, position.y - 1);
		sourroundingNodes[4] = getNode(position.x    , position.y - 1);
		sourroundingNodes[5] = getNode(position.x - 1, position.y - 1);
		sourroundingNodes[6] = getNode(position.x - 1, position.y    );
		sourroundingNodes[7] = getNode(position.x - 1, position.y + 1);

		break;
	}
	return sourroundingNodes;
}

int Pathfinding::NodeMap::numSurroundingNodes() const {
	switch(this->moveableDirections) {
	case FOUR:
		return 4;
		break;
	case EIGHT:
		return 8;
		break;
	}
}

void Pathfinding::NodeMap::setMoveableDirectionNodes(const Pathfinding::MoveableDirections directions) {
	this->moveableDirections = directions;
}

Pathfinding::PathNode* Pathfinding::NodeMap::getNode(const Pathfinding::Vector2i position) {
	if(insideBounds(position.x, position.y)) {
		return &nodes[position.x][position.y];
	}
	return NULL;
}

Pathfinding::PathNode* Pathfinding::NodeMap::getNode(int x, int y) {
	if(insideBounds(x, y)) {
		return &nodes[x][y];
	}
	return NULL;
}

void Pathfinding::NodeMap::setNode(const Pathfinding::Vector2i position, Pathfinding::PathNode node) {
	if(insideBounds(position.x, position.y)) {
		nodes[position.x][position.y] = node;
	}
}

void Pathfinding::NodeMap::setNode(const int x, const int y, Pathfinding::PathNode node) {
	if(insideBounds(x, y)) {
		nodes[x][y] = node;
	}
}

int Pathfinding::NodeMap::getWidth() const {
	return this->width;
}

int Pathfinding::NodeMap::getHeight() const {
	return this->height;
}

bool Pathfinding::NodeMap::contains(const Pathfinding::Vector2i nodePosition) const {
	return insideBounds(nodePosition.x, nodePosition.y);
}
