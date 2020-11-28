#pragma once
#ifndef __SIM2_SCENE__
#define __SIM2_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Label.h"

//Game Objects
#include "Ball.h"
#include "Brick.h"
#include "Border.h"

class Sim2Scene : public Scene
{
public:
	Sim2Scene();
	~Sim2Scene();

	// Scene LifeCycle Functions
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

	void handleCollisions();

private:
	// IMGUI Function
	void GUI_Function() const;

	std::string m_guiTitle;

	glm::vec2 m_mousePosition;

	
	bool m_playerFacingRight;

	//Game Objects
	Brick* m_pBrick;
	Ball* m_pBall;

	// UI Items
	Button* m_pReturnButton;
	Label* m_pInstructionsLabel;

	const float deltaTime = 1.0 / 300.0f;

	//Borders 
	Border* leftBorder;
	Border* rightBorder;
	Border* topBorder;
	Border* bottomBorder;

	std::vector<Border*> borders;

};

#endif /* defined (__SIM2_SCENE__) */