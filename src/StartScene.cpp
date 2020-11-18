#include "StartScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

StartScene::StartScene()
{
	StartScene::start();
}

StartScene::~StartScene()
= default;

void StartScene::draw()
{

	TextureManager::Instance()->draw("StartScreen", 400, 300, 0, 255, true);

	drawDisplayList();
}

void StartScene::update()
{
	updateDisplayList();
}

void StartScene::clean()
{
	removeAllChildren();
}

void StartScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if(EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(SIM1_SCENE);
	}
}

void StartScene::start()
{

	TextureManager::Instance()->load("../Assets/textures/StartScreen.png", "StartScreen");

	const SDL_Color blue = { 0, 0, 255, 255 };
	
	// Sim 1 Button
	m_pSim1Button = new Button("../Assets/textures/Sim1Button.png", "Sim1Button", START_BUTTON);
	m_pSim1Button->getTransform()->position = glm::vec2(250.0f, 240.0f); 

	m_pSim1Button->addEventListener(CLICK, [&]()-> void
	{
		m_pSim1Button->setActive(false);
		TheGame::Instance()->changeSceneState(SIM1_SCENE);
	});
	
	m_pSim1Button->addEventListener(MOUSE_OVER, [&]()->void
	{
		m_pSim1Button->setAlpha(128);
	});

	m_pSim1Button->addEventListener(MOUSE_OUT, [&]()->void
	{
		m_pSim1Button->setAlpha(255);
	});
	addChild(m_pSim1Button);

	//Sim2 Button
	m_pSim2Button = new Button("../Assets/textures/Sim2Button.png", "Sim2Button", START_BUTTON);
	m_pSim2Button->getTransform()->position = glm::vec2(550.0f, 240.0f);

	m_pSim2Button->addEventListener(CLICK, [&]()-> void
		{
			m_pSim2Button->setActive(false);
			TheGame::Instance()->changeSceneState(SIM2_SCENE);
		});

	m_pSim2Button->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pSim2Button->setAlpha(128);
		});

	m_pSim2Button->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pSim2Button->setAlpha(255);
		});
	addChild(m_pSim2Button);


	//Instructions Button
	m_pInstructButton = new Button("../Assets/textures/InstructionsButton.png", "InstructionButton", INSTRUCT_BUTTON);
	m_pInstructButton->getTransform()->position = glm::vec2(400.0f, 350.0f);

	m_pInstructButton->addEventListener(CLICK, [&]()-> void
		{
			m_pInstructButton->setActive(false);
			TheGame::Instance()->changeSceneState(INSTRUCT_SCENE);
		});

	m_pInstructButton->addEventListener(MOUSE_OVER, [&]()->void
		{
			m_pInstructButton->setAlpha(128);
		});

	m_pInstructButton->addEventListener(MOUSE_OUT, [&]()->void
		{
			m_pInstructButton->setAlpha(255);
		});
	addChild(m_pInstructButton);

	
}

