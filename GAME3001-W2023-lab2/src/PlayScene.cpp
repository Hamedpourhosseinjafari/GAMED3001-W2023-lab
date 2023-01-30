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
	if(m_bDebugView)
	{
		Util::DrawCircle(m_pTarget->GetTransform()->position, m_pTarget->GetWidth() * 0.5f);

		if(m_pStarShip->IsEnabled())
		{
			Util::DrawRect(m_pStarShip->GetTransform()->position - 
				glm::vec2(m_pStarShip->GetWidth() * 0.5f, m_pStarShip->GetHeight() * 0.5f), m_pStarShip->GetWidth(), m_pStarShip->GetHeight());

			CollisionManager::RotateAABB(m_pStarShip, m_pStarShip->GetCurrentHeading());
		}
	}
}

void PlayScene::Update()
{
	UpdateDisplayList();
	if(m_pStarShip->IsEnabled())
	{
		CollisionManager::CircleAABBCheck(m_pTarget, m_pStarShip);
	}
}

void PlayScene::Clean()
{
	RemoveAllChildren();
}

void PlayScene::HandleEvents()
{
	EventManager::Instance().Update();

	
	

	// handle player movement if no Game Controllers found

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
	m_bDebugView = false; //turn off debug colliders
	// add the target to the scene
	m_pTarget = new Target();
	m_pTarget->GetTransform()->position = glm::vec2(500.0f, 100.0f);
	AddChild(m_pTarget);


	// preload sounds

	SoundManager::Instance().Load("../Assets/Audio/yay.ogg", "yay", SoundType::SOUND_SFX);

	//add the starship to the scene
	m_pStarShip = new StarShip();
	m_pStarShip->GetTransform()->position = glm::vec2(100.0f, 400.0f);
	m_pStarShip->SetTargetPosition(m_pTarget->GetTransform()->position);
	m_pStarShip->SetCurrentDirection(glm::vec2(1.0f, 0.0f)); // facing right
	m_pStarShip->SetEnabled(false);
	AddChild(m_pStarShip);

	ImGuiWindowFrame::Instance().SetGuiFunction(std::bind(&PlayScene::GUI_Function, this));
	
}

void PlayScene::GUI_Function() 
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("GAME3001-W2023-lab2", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	ImGui::Separator();

	//debug properties
	static bool toggleDebug;
	if(ImGui::Checkbox("toggle debug", &toggleDebug))
	{
		m_bDebugView = toggleDebug;
	}
	ImGui::Separator();
	
	//target properties
	static float position[2] = { m_pTarget->GetTransform()->position.x,m_pTarget->GetTransform()->position.y };

	if (ImGui::SliderFloat2("target position",position,0.0f,800.0f))
	{
		m_pTarget->GetTransform()->position = glm::vec2(position[0],position[1]);
		m_pStarShip->SetTargetPosition(m_pTarget->GetTransform()->position);
	}
	ImGui::Separator();
	//starship properties
	static bool toggleseek = m_pStarShip->IsEnabled();
	if(ImGui::Checkbox("toggle seek",&toggleseek))
	{
		m_pStarShip->SetEnabled(toggleseek);
	}
	ImGui::Separator();

	static float acceleration = m_pStarShip->GetMaxSpeed();
	if(ImGui::SliderFloat("acceleration rate", &acceleration, 0.0f,50.0f))
	{
		m_pStarShip->SetAcceletaionRate(acceleration);
		m_pStarShip->GetRigidBody()->acceleration = m_pStarShip->GetCurrentDirection() * m_pStarShip->GetAccelerationRate();
	}
	ImGui::Separator();
	static float turn_rate = m_pStarShip->GetMaxSpeed();
	if (ImGui::SliderFloat("turn` rate", &turn_rate, 0.0f, 20.0f))
	{
		m_pStarShip->SetTurnRate(turn_rate);
	}
	ImGui::Separator();
	if(ImGui::Button("reset"))
	{
		//reset starship pos
		m_pStarShip->GetTransform()->position = glm::vec2(100.0f, 400.0f);
		//reset the target position
		m_pTarget->GetTransform()->position = glm::vec2(500.0f, 100.0f);

		//reset current heading
		m_pStarShip->SetCurrentHeading(0.0f);
		m_pStarShip->SetCurrentDirection(glm::vec2(1.0f, 0.0f));


		//reset Acceleration rate
		m_pStarShip->SetAcceletaionRate(4.0f);

		//reset the turn rate
		m_pStarShip->SetTurnRate(5.0f);
		//reset the target for the starship
		m_pStarShip->SetTargetPosition(m_pTarget->GetTransform()->position);
	}
	ImGui::End();
}


