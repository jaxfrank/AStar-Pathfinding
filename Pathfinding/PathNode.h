#ifndef PATH_NODE
#define PATH_NODE

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

#include "Vector2i.h"

namespace Pathfinding {
	struct __declspec(dllexport) PathNode {
		PathNode* parent;
		int h_heuristic;
		int g_movementCost;
		int f_total;
		int cost;
		bool inOpenList;
		bool inClosedList;
		Vector2i position;

		PathNode(): 
			parent(NULL),
			h_heuristic(-1),
			g_movementCost(0),
			f_total(1),
			cost(1),
			position(0,0),
			inOpenList(false),
			inClosedList(false)
		{}

		inline void calcF() { f_total = g_movementCost + f_total; }

		struct CompareLessPtr {
			bool operator()( const PathNode* lhs, const PathNode* rhs ) const {
				return lhs->f_total < rhs->f_total;
			}
		};
		struct CompareLessRef {
			bool operator()( const PathNode& lhs, const PathNode& rhs ) const {
				return lhs.f_total < rhs.f_total;
			}
		};
	};
}

#endif