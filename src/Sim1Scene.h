#pragma once
#ifndef __SIM1_SCENE__
#define __SIM1_SCENE__

#include "Scene.h"
#include "Button.h"
#include "Label.h"

//Game Objects
#include "Crate.h"
#include "Triangle.h"

class Sim1Scene : public Scene
{
public:
	Sim1Scene();
	~Sim1Scene();

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

	// UI Items
	Button* m_pReturnButton;
	Label* m_pInstructionsLabel;
};

#endif /* defined (__SIM1_SCENE__) */