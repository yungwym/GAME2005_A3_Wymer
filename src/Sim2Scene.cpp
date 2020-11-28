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


	if (CollisionManager::circleAABBCheck(m_pBall, m_pBrick))
	{
		std::cout << "Collision With Brick" << std::endl;

		//Change directions 
		m_pBall->getRigidBody()->velocity = -(m_pBall->getRigidBody()->velocity) * 0.8f;
		m_pBall->getTransform()->position += m_pBall->getRigidBody()->velocity * deltaTime;
	}

	for (auto border : borders)
	{
		if (CollisionManager::circleAABBCheck(m_pBall, border))
		{

			std::cout << "COLLISION WITH BORDER" << std::endl;

			m_pBall->getRigidBody()->velocity = -(m_pBall->getRigidBody()->velocity) * 0.8f;
			m_pBall->getTransform()->position += m_pBall->getRigidBody()->velocity * deltaTime;
		}
	}
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
				
			}
			else if (EventManager::Instance().getGameController(0)->LEFT_STICK_X < -deadZone)
			{
			
			}
		}
	}


	// handle player movement if no Game Controllers found
	if (SDL_NumJoysticks() < 1)
	{
		if (EventManager::Instance().isKeyDown(SDL_SCANCODE_A))
		{
			if (m_pBrick->getTransform()->position.x > 150)
			{
				std::cout << m_pBrick->getTransform()->position.x << std::endl;

				m_pBrick->moveLeft();
			}
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			if (m_pBrick->getTransform()->position.x < 650)
			{
				m_pBrick->moveRight();
			}
		}
		else
		{
			m_pBrick->stopMovement();
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

	//Game Objects 
	m_pBall = new Ball();
	addChild(m_pBall);

	m_pBrick = new Brick();
	addChild(m_pBrick);

	

	leftBorder = new Border(glm::vec2(100, 120), 2, 600);
	rightBorder = new Border(glm::vec2(700, 120), 2, 600);
	topBorder = new Border(glm::vec2(0, 120), 600, 2);
	bottomBorder = new Border(glm::vec2(0, 600), 1000, 2);

	addChild(leftBorder);
	addChild(rightBorder);
	addChild(topBorder);
	addChild(bottomBorder);
	
	borders.push_back(leftBorder);
	borders.push_back(rightBorder);
	borders.push_back(bottomBorder);
	borders.push_back(topBorder);
	



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

	ImGui::Text("Ball Velocity : ");

	

	ImGui::End();

	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();
}