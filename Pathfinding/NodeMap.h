#ifndef NODE_MAP
#define NODE_MAP

#include <vector>
#include <array>

namespace Pathfinding {
	enum __declspec(dllexport) MoveableDirections {
		FOUR,
		EIGHT
	};

	struct PathNode;
	struct Vector2i;

	class __declspec(dllexport) NodeMap {
	public:
		NodeMap(int width, int height);

		PathNode** getSurroundingNodes(const Vector2i position); //Returns an array of PathNode pointers
		PathNode* getNode(const Vector2i position);
		PathNode* getNode(int x, int y);
		void setNode(const Vector2i position, PathNode node);
		void setNode(const int x, const int y, PathNode node);

		int getWidth() const;
		int getHeight() const;

		bool contains(const Vector2i nodePosition) const;
		int numSurroundingNodes() const;
		void setMoveableDirectionNodes(const MoveableDirections directions);
	private:
		std::vector<std::vector<PathNode>> nodes;
		MoveableDirections moveableDirections;
		int width;
		int height;

		inline bool insideBounds(const int x, const int y) const {return x >= 0 && x < width && y >= 0 && y < height; }
		inline bool outsideBounds(const int x, const int y) const {return x < 0 || x >= width || y < 0 || y >= height; }
	};
}

#endif