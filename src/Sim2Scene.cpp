#include "Sim2Scene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

Sim2Scene::Sim2Scene()
{
	Sim2Scene::start();
}

Sim2Scene::~Sim2Scene()
= default;

void Sim2Scene::draw()
{
	TextureManager::Instance()->draw("Sim2Screen", 400, 300, 0, 255, true);

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void Sim2Scene::update()
{
	updateDisplayList();
}

void Sim2Scene::clean()
{
	removeAllChildren();
}

void Sim2Scene::handleEvents()
{
	EventManager::Instance().update();

	// handle player movement with GameController
	if (SDL_NumJoysticks() > 0)
	{
		if (EventManager::Instance().getGameController(0) != nullptr)
		{
			const auto deadZone = 10000;
			if (EventManager::Instance().getGameController(0)->LEFT_STICK_X > deadZone)
			{
				//m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
				m_playerFacingRight = true;
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
				//	m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
				m_playerFacingRight = false;
			}
			else
			{
				if (m_playerFacingRight)
				{
					//m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
				}
				else
				{
					//m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
				}
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			//	m_pPlayer->setAnimationState(PLAYER_RUN_LEFT);
			m_playerFacingRight = false;
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			//m_pPlayer->setAnimationState(PLAYER_RUN_RIGHT);
			m_playerFacingRight = true;
		}
		else
		{
			if (m_playerFacingRight)
			{
				//m_pPlayer->setAnimationState(PLAYER_IDLE_RIGHT);
			}
			else
			{
				//m_pPlayer->setAnimationState(PLAYER_IDLE_LEFT);
			}
		}
	}


	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(START_SCENE);
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_2))
	{
		TheGame::Instance()->changeSceneState(END_SCENE);
	}
}

void Sim2Scene::start()
{

	//Load Background and Textures 
	TextureManager::Instance()->load("../Assets/textures/Sim2_Background.png", "Sim2Screen");

	// Set GUI Title
	m_guiTitle = "Play Scene";


	/* Instructions Label */
	m_pInstructionsLabel = new Label("Press the backtick (`) character to toggle Debug View", "Consolas", 10.0f);
	m_pInstructionsLabel->getTransform()->position = glm::vec2(Config::SCREEN_WIDTH * 0.5f, 587.5f);

	addChild(m_pInstructionsLabel);

	//Return Button
	m_pReturnButton = new Button("../Assets/textures/ReturnSimButton.png", "ReturnSimButton", RETURN_BUTTON);
	m_pReturnButton->getTransform()->position = glm::vec2(680.0f, 60.0f);

	m_pReturnButton->addEventListener(CLICK, [&]()-> void
		{
			m_pReturnButton->setActive(false);
			TheGame::Instance()->changeSceneState(START_SCENE);
		});

	m_pReturnButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pReturnButton->setAlpha(128);
		});

	m_pReturnButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pReturnButton->setAlpha(255);
		});
	addChild(m_pReturnButton);
}

void Sim2Scene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();

	ImGui::Begin("Game Physics - Assignment 3: Collision Response", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);


	if (ImGui::Button("Activate Simulation"))
	{
		
	}

	

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}