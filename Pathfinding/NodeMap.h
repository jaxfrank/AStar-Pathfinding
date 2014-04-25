#ifndef NODE_MAP
#define NODE_MAP

/*
*The MIT License (MIT)
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