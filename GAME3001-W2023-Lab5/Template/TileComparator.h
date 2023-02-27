#pragma once
#ifndef __TILE_COMPARATOR__
#define __TILE_COMPARATOR__

#include "Tile.h"

class TileComparator
{
	int operator() (const Tile* lhs, const Tile* rhs)
	{
		return lhs->GetTileCost() > rhs->GetTileCost();
	}
};

#endif 
