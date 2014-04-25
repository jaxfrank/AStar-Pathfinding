#ifndef PATHFINDER
#define PATHFINDER

namespace Pathfinding {
	class NodeMap;
	struct Vector2i;
	class __declspec(dllexport) Pathfinder {
	public:
		Pathfinder(void);
		~Pathfinder(void);

		void findPath(NodeMap* nodeMap, Vector2i start, Vector2i end);
		int calcH(const Vector2i start, const Vector2i begin, const Vector2i end) const;
	};
}

#endif
