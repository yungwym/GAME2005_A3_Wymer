#pragma once
#ifndef __OBJECT_POOL__
#define __OBJECT_POOL__

#include "Projectile.h"

using namespace std;


class ObjectPool
{

public:
	ObjectPool(int);
	~ObjectPool();

	Projectile* Spawn();
	void Despawn(Projectile*);

	std::vector<Projectile*> allProjectiles;
	
private:

	std::vector<Projectile*> activeProjectiles;
	std::vector<Projectile*> inactiveProjectiles;
};


#endif // !__OBJECT_POOL__
