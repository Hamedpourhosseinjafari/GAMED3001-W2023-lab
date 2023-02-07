#pragma once
#ifndef __TILE__
#define __TILE__

#include "Label.h"
#include  "NavigationObject.h"
#include "TileStatus.h"
#include "NeighbourTile .h"
class Tile : public NavigationObject
{
public:
	//constructor
	Tile();

	// Destructor
	~Tile();
	// Life-Cycle Functions
	void Draw()override;
	void Update() override;
	void Clean() override;


	// Getter (Accessors) and setters(mutators)
	Tile* GetNeighbourTile(NeighbourTile position) const;
	void SetNeighbourTile(NeighbourTile position, Tile* tile);

	float GetTileCost() const;
	void SetTileCost(float cost);

	TileStatus GetTileStatus()const;
	void SetTileStatus(TileStatus status);

	// Utility function
	void AddLabels();
	void SetlabelsEnabled(bool state) const;

private:
	// Private Instance Members (fields)
	float m_cost;
	TileStatus m_status;

	Label* m_costLable;
	Label* m_statuslable;

	Tile* m_neighbours[NUM_OF_NEIGHBOUR_TILES];
};

#endif/* DEFINED (__TILE__)*/
