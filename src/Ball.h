#pragma once
#ifndef __BALL__
#define __BALL__

#include "Sprite.h"


class Ball : public Sprite 
{
	public:
		Ball();
		~Ball();

		// Life Cycle Methods
		virtual void draw() override;
		virtual void update() override;
		virtual void clean() override;

private:

	const float deltaTime = 1.0f / 60.f;
	glm::vec2 gravity = glm::vec2(0, 9.8);

};




#endif // __BALL__
