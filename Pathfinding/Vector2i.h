#ifndef VECTOR2I
#define VECTOR2I

namespace Pathfinding {
	struct __declspec(dllexport) Vector2i{
		int x;
		int y;

		Vector2i(int x, int y) : x(x), y(y) {}
		inline bool operator==(Vector2i& other)const {
			return x == other.x && y == other.y;
		}
	};
}

#endif