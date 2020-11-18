#include "InstructScene.h"
#include <algorithm>
#include "Game.h"
#include "glm/gtx/string_cast.hpp"
#include "EventManager.h"

InstructScene::InstructScene()
{
	InstructScene::start();
}

InstructScene::~InstructScene()
= default;

void InstructScene::draw()
{

	TextureManager::Instance()->draw("InstructScreen", 400, 300, 0, 255, true);

	drawDisplayList();
}

void InstructScene::update()
{
	updateDisplayList();
}

void InstructScene::clean()
{
	removeAllChildren();
}

void InstructScene::handleEvents()
{
	EventManager::Instance().update();

	// Keyboard Events
	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->quit();
	}

	if (EventManager::Instance().isKeyDown(SDL_SCANCODE_1))
	{
		TheGame::Instance()->changeSceneState(SIM1_SCENE);
	}
}

void InstructScene::start()
{
	TextureManager::Instance()->load("../Assets/textures/InstructScreen.png", "InstructScreen");

	const SDL_Color blue = { 0, 0, 255, 255 };

	// Sim 1 Button
	m_pSim1Button = new Button("../Assets/textures/ReturnButton.png", "ReturnButton", RETURN_BUTTON);
	m_pSim1Button->getTransform()->position = glm::vec2(400.0f, 475.0f);

	m_pSim1Button->addEventListener(CLICK, [&]()-> void
		{
			m_pSim1Button->setActive(false);
			TheGame::Instance()->changeSceneState(START_SCENE);
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
}

