#include "PlayScene.h"
#include "Game.h"
#include "EventManager.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"
#include "Util.h"

PlayScene::PlayScene()
{
	PlayScene::Start();
}

PlayScene::~PlayScene()
= default;

void PlayScene::Draw()
{
	DrawDisplayList();
	

	SDL_SetRenderDrawColor(Renderer::Instance().GetRenderer(), 255, 255, 255, 255);
}

void PlayScene::Update()
{
	UpdateDisplayList();

}

void PlayScene::Clean()
{
	RemoveAllChildren();
}

void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		Game::Instance().Quit();
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_1))
	{
		Game::Instance().ChangeSceneState(SceneState::START);
	}

	if (EventManager::Instance().IsKeyDown(SDL_SCANCODE_2))
	{
		Game::Instance().ChangeSceneState(SceneState::END);
	}
}

void PlayScene::Start()
{
	// Set GUI Title
	m_guiTitle = "Play Scene";

	m_buildGrid(); // construct a grid of connected tiles

	m_setGridEnabled(true);
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);

	// Add the Target to the Scene
	m_pTarget = new Target(); // instantiate an object of type Target
	m_pTarget->GetTransform()->position = m_GetTile(15, 11)->GetTransform()->position + offset;
	m_pTarget->SetGridPosition(15.0f, 11.0f);
	m_GetTile(15, 11)->SetTileStatus(GOAL);
	AddChild(m_pTarget);

	// Add the StarShip to the Scene
	m_pStarShip = new StarShip();
	m_pStarShip->GetTransform()->position = m_GetTile(1, 3)->GetTransform()->position + offset;
	m_pStarShip->SetGridPosition(1.0f, 3.0f);
	m_GetTile(1, 3)->SetTileStatus(START);
	AddChild(m_pStarShip);

	

	// Preload Sounds

	SoundManager::Instance().Load("../Assets/Audio/yay.ogg", "yay", SoundType::SOUND_SFX);
	SoundManager::Instance().Load("../Assets/Audio/thunder.ogg", "thunder", SoundType::SOUND_SFX);

	ImGuiWindowFrame::Instance().SetGuiFunction(std::bind(&PlayScene::GUI_Function, this));
}

void PlayScene::m_buildGrid()
{
	const auto tile_size = Config::TILE_SIZE;

	// layout a grid of tiles (20 x 15)
	for(int row = 0 ;row < Config::ROW_NUM;++row)
	{
		for (int col = 0 ; col < Config::COL_NUM;++col)
		{
			Tile* tile = new Tile();
			tile->GetTransform()->position = glm::vec2(col * tile_size, row * tile_size);
			tile->SetGridPosition(col,row);
			tile->SetParent(this);
			tile->AddLabels();
			AddChild(tile);
			tile->SetEnabled(false);
			m_pGrid.push_back(tile);
		}
	}

	// setup the neighbour refrences for each tile in the grid
	// tiles = nodes in our graph
	for (int row = 0; row < Config::ROW_NUM; ++row)
	{
		for (int col = 0; col < Config::COL_NUM; ++col)
		{
			Tile* tile = m_GetTile(col, row);

			// top most Neighbour
			if(row == 0)
			{
				tile->SetNeighbourTile(TOP_TILE, nullptr);
			}
			else
			{
				tile->SetNeighbourTile(TOP_TILE, m_GetTile(col, row - 1));
			}

			// right most Neighbour
			if(col == Config::COL_NUM - 1)
			{
				tile->SetNeighbourTile(RIGHT_TILE, nullptr);
			}
			else
			{
				tile->SetNeighbourTile(RIGHT_TILE, m_GetTile(col + 1, row));
;			}

			// botom most Neighbour
			if (row == Config::ROW_NUM - 1)
			{
				tile->SetNeighbourTile(BOTTOM_TILE, nullptr);
			}
			else
			{
				tile->SetNeighbourTile(BOTTOM_TILE, m_GetTile(col, row + 1));
			}

			// left most Neighbour
			if (col == 0)
			{
				tile->SetNeighbourTile(LEFT_TILE, nullptr);
			}
			else
			{
				tile->SetNeighbourTile(LEFT_TILE, m_GetTile(col - 1, row));
				;
			}
		}
	}
}

bool PlayScene::m_getGridEnable() const
{
	return m_isGridEnabled;
}

void PlayScene::m_setGridEnabled(bool state)
{
	m_isGridEnabled = state;
	for (auto tile : m_pGrid)
	{
		tile->SetEnabled(m_isGridEnabled); // toggle each tile object
		tile->SetlabelsEnabled(m_isGridEnabled); // toggles each label object within the tile
	}
}

void PlayScene::m_computeTileCost()
{
	// for next lab (4b)
}

Tile* PlayScene::m_GetTile(const int col, int row) const
{
	return m_pGrid[(row * Config::COL_NUM) + col];
}

Tile* PlayScene::m_getTile (const glm::vec2 grid_position) const
{
	const auto col = grid_position.x;
	const auto row = grid_position.y;
	return m_GetTile(col, row);
}

void PlayScene::GUI_Function()
{
	auto offset = glm::vec2(Config::TILE_SIZE * 0.5f, Config::TILE_SIZE * 0.5f);

	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("GAME3001 - W2023 - Lab4", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar );

	ImGui::Separator();

	// Debug Properties
	static bool toggle_grid = false;
	if(ImGui::Checkbox("Toggle Debug Grid", &toggle_grid))
	{
		m_bDebugView = toggle_grid;
		m_setGridEnabled(m_isGridEnabled);
	}

	ImGui::Separator();

   // starship porperties
	static int start_position[2] = {
		static_cast<int> (m_pStarShip->GetGridPosition().x),
		static_cast<int> (m_pStarShip->GetGridPosition().y)
	};
	if(ImGui::SliderInt2("start pos",start_position,0,Config::COL_NUM -1))
	{
		if (start_position[1] > Config::ROW_NUM -1)
		{
			start_position[1] = Config::ROW_NUM - 1;
		}
	}

	//
	m_getTile(m_pStarShip->GetGridPosition())->SetTileStatus(UNVISITED);
	m_pStarShip->GetTransform()->position = m_GetTile(start_position[0], start_position[1])->GetTransform()->position + offset;
	m_pStarShip->SetGridPosition(start_position[0], start_position[1]);
	m_getTile(m_pStarShip->GetGridPosition())->SetTileStatus(START);

	// Target Properties
	
	ImGui::Separator();

		static int goal_position[2] = {
		static_cast<int> (m_pTarget->GetGridPosition().x),
		static_cast<int> (m_pTarget->GetGridPosition().y)
	};
	if(ImGui::SliderInt2("goal pos", goal_position,0,Config::COL_NUM -1))
	{
		if (goal_position[1] > Config::ROW_NUM -1)
		{
			goal_position[1] = Config::ROW_NUM - 1;
		}
	}

	//
	m_getTile(m_pTarget->GetGridPosition())->SetTileStatus(UNVISITED);
	m_pTarget->GetTransform()->position = m_GetTile(goal_position[0], goal_position[1])->GetTransform()->position + offset;
	m_pTarget->SetGridPosition(goal_position[0], goal_position[1]);
	m_getTile(m_pTarget->GetGridPosition())->SetTileStatus(GOAL);

	ImGui::Separator();

	// StarShip Properties
	

	ImGui::Separator();

	

	
	ImGui::End();
}


