#ifndef PATH_NODE
#define PATH_NODE

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