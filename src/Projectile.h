#pragma once
#ifndef __PROJECTILE__
#define __PROJECTILE__

#include "Sprite.h"


class Projectile : public Sprite
{
public:
	Projectile();
	~Projectile();
	
	//Life Cycle Methods 
	virtual void draw() override;
	virtual void update() override;
	virtual void clean() override;

	void Reset();

	bool active = false;

private:
	

};

#endif // !__PROJECTILE__
