#include "ObjectPool.h"

#include <iostream>

using namespace std;

ObjectPool::ObjectPool(int size)
{
	for (int i = 0; i < size; i++)
	{
		Projectile* proj = new Projectile();

		inactiveProjectiles.push_back(proj);
		allProjectiles.push_back(proj);
	}
}

ObjectPool::~ObjectPool()
= default;

Projectile* ObjectPool::Spawn()
{
	Projectile* projectile = NULL;

	if (inactiveProjectiles.size() > 0)
	{
		projectile = inactiveProjectiles.back();
		projectile->active = true;
		projectile->Reset();
		inactiveProjectiles.pop_back();
		activeProjectiles.push_back(projectile);
		std::cout << "SPAWNED" << std::endl;
		std::cout << "Active Count: " << std::to_string(activeProjectiles.size()) << std::endl;

	}
	else
	{
		std::cout << "Error: Projectile could not be spawned. Max Limit Reached." << std::endl;
	}
	return projectile;
}


void ObjectPool::Despawn(Projectile* projectile)
{
	projectile->active = false;
	inactiveProjectiles.push_back(projectile);

	for (std::vector<Projectile*>::iterator iter = activeProjectiles.begin(); iter != activeProjectiles.end(); iter++)
	{
		if (*iter == projectile)
		{
			activeProjectiles.erase(iter);
			std::cout << "DESPAWNED" << std::endl;
			std::cout << "Active Count: " << std::to_string(activeProjectiles.size()) << std::endl;
			return;
		}
	}
}