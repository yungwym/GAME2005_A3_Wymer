#include "Projectile.h"
#include "TextureManager.h"

Projectile::Projectile()
{
	

	TextureManager::Instance()->load("../Assets/textures/Projectile.png", "Projectile");

	auto size = TextureManager::Instance()->getTextureSize("Projectile");
	setWidth(size.x);
	setHeight(size.y);

	getTransform()->position = glm::vec2(205.0f, 137.5f);

	setType(PROJECTILE);

	Reset();
}

Projectile::~Projectile()
= default;


void Projectile::draw()
{
	if (active)
	{
		const auto x = getTransform()->position.x;
		const auto y = getTransform()->position.y;

		TextureManager::Instance()->draw("Projectile", x, y, 0, 255, true);
	}
}

void Projectile::update()
{
	if (active)
	{
		float deltaTime = 1.0f / 60.0f;

		getRigidBody()->velocity = getRigidBody()->velocity + (getRigidBody()->acceleration * deltaTime);
		getTransform()->position = getTransform()->position + getRigidBody()->velocity * deltaTime;
	}	
}


void Projectile::clean()
{


}


void Projectile::Reset()
{
	getRigidBody()->velocity = glm::vec2(0.0f, 20.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 9.8f);
	getRigidBody()->isColliding = false;
}


