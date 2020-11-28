#pragma once
#ifndef __BORDER__
#define __BORDER__

#include "Sprite.h"


class Border : public Sprite
{

public:

	Border(glm::vec2 pos, int width, int height);
	~Border();


	// Life Cycle Methods
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

private:


};


#endif // __BORDER__

