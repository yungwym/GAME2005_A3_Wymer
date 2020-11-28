#pragma once
#ifndef __BRICK__
#define __BRICK__

#include "Sprite.h"


class Brick : public Sprite
{

public:
	Brick();
	~Brick();

	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void moveLeft();
	void moveRight();

	void stopMovement();

private:
	const float SPEED = 150.0f;

	const float deltaTime = 1.0f / 60.0f; 

};

#endif // !__BRICK__
