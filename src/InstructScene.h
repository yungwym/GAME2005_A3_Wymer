#pragma once
#ifndef __INSTRUCT_SCENE__
#define __INSTRUCT_SCENE__

#include "Scene.h"
#include "Label.h"
#include "ship.h"
#include "Button.h"

class InstructScene final : public Scene
{
public:
	InstructScene();
	~InstructScene();

	// Inherited via Scene
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;
	virtual void handleEvents() override;
	virtual void start() override;

private:
	Label* m_pStartLabel{};
	Label* m_pInstructionsLabel{};

	Ship* m_pShip{};

	Button* m_pSim1Button;
	Button* m_pSim2Button;
	Button* m_pInstructButton;
};

#endif /* defined (__INSTRUCT_SCENE__) */