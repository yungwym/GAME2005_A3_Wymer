#include "Sim1Scene.h"
#include "Game.h"
#include "EventManager.h"
#include "Util.h"

// required for IMGUI
#include "imgui.h"
#include "imgui_sdl.h"
#include "Renderer.h"

Sim1Scene::Sim1Scene()
{
	Sim1Scene::start();
}

Sim1Scene::~Sim1Scene()
= default;

void Sim1Scene::draw()
{
	TextureManager::Instance()->draw("Sim1Screen", 400, 300, 0, 255, true);

	drawDisplayList();
	SDL_SetRenderDrawColor(Renderer::Instance()->getRenderer(), 255, 255, 255, 255);

	if (EventManager::Instance().isIMGUIActive())
	{
		GUI_Function();
	}
}

void Sim1Scene::update()
{
	updateDisplayList();

	if (SDL_GetTicks() - projectileSpawnTimerStart >= projectileSpawnTimerDuration)
	{
		SpawnProjectile();
	}

	std::vector<Projectile*>& allProjs = m_pObjectPool->allProjectiles;

	for (auto bomb : allProjs)
	{
		if (CollisionManager::AABBCheck(m_pPlayer, bomb))
		{
			std::cout << "Collision" << std::endl;
			m_pObjectPool->Despawn(bomb);
		}
	}

	for (std::vector<Projectile*>::iterator iter = allProjs.begin(); iter != allProjs.end(); ++iter)
	{
		Projectile* proj = *iter;

		if (proj->active && proj->getTransform()->position.y >= 650)
		{
			m_pObjectPool->Despawn(proj);
			break;
		}
	}
}

void Sim1Scene::clean()
{
	removeAllChildren();
}

void Sim1Scene::handleEvents()
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
			m_pPlayer->moveLeft();
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_D))
		{
			m_pPlayer->moveRight();
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_W))
		{
			m_pPlayer->moveUp();
		}
		else if (EventManager::Instance().isKeyDown(SDL_SCANCODE_S)) 
		{
			m_pPlayer->moveDown();
		}
		else
		{
			m_pPlayer->stopMovement();
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

void Sim1Scene::start()
{
	//Load Background and Textures 
	TextureManager::Instance()->load("../Assets/textures/Sim1_Background.png", "Sim1Screen");

	SoundManager::Instance().load("../Assets/audio/thunder.ogg", "thunder", SOUND_SFX);

	// Set GUI Title
	m_guiTitle = "Play Scene";
	
	// Player Sprite
	m_pPlayer = new Player();
	addChild(m_pPlayer);

	//Object Pool
	m_pObjectPool = new ObjectPool(10);

	for (std::vector<Projectile*>::iterator iter = m_pObjectPool->allProjectiles.begin(); iter != m_pObjectPool->allProjectiles.end(); ++iter)
	{
		Projectile* proj = *iter;
		addChild(proj);
	}

	projectileSpawnTimerStart = SDL_GetTicks();

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

void Sim1Scene::SpawnProjectile()
{
	Projectile* proj = m_pObjectPool->Spawn();
	if (proj)
	{
		proj->getTransform()->position = glm::vec2(50 + rand() % 700, 130);
	}

	projectileSpawnTimerStart = SDL_GetTicks();
}




void Sim1Scene::GUI_Function() const
{
	// Always open with a NewFrame
	ImGui::NewFrame();

	// See examples by uncommenting the following - also look at imgui_demo.cpp in the IMGUI filter
	//ImGui::ShowDemoWindow();
	
	ImGui::Begin("Game Physics - Assignment 3: Collision Detection", NULL, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_MenuBar);

	
	if(ImGui::Button("Activate Simulation"))
	{
		
	}

	ImGui::Separator();



	ImGui::End();
	
	// Don't Remove this
	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
	ImGui::StyleColorsDark();





}



