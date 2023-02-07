#pragma once
#ifndef __PLAY_SCENE__
#define __PLAY_SCENE__

#include "Scene.h"
#include "Target.h"
#include "StarShip.h"
#include "Tile.h"


class PlayScene : public Scene
{
public:
	PlayScene();
	~PlayScene() override;

	// Scene LifeCycle Functions
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Clean() override;
	virtual void HandleEvents() override;
	virtual void Start() override;
private:
	// IMGUI Function
	void GUI_Function();
	std::string m_guiTitle;
	glm::vec2 m_mousePosition;

	// Game Objects for the Scene
	Target* m_pTarget;
	StarShip* m_pStarShip;
	

	// Debugging Variables
	bool m_bDebugView;

	// Pathfinding objects and functions
	std::vector<Tile*> m_pGrid;
	bool m_isGridEnabled;

	void m_buildGrid();
	bool m_getGridEnable()const ;
	void m_setGridEnabled(bool state);
	void m_computeTileCost(); // future use(lab4b)

	//convenience functions to convert from world space to grid space
	Tile* m_GetTile(int col, int row)const;
	Tile* m_getTile(glm::vec2 grid_position);

	//heuristic
	// well add this in later(lab 4b)

};

#endif /* defined (__PLAY_SCENE__) */