#include "Brick.h"
#include "TextureManager.h"


Brick::Brick()
{
	TextureManager::Instance()->load("../Assets/textures/Brick.png", "Brick");

	getTransform()->position = glm::vec2(400.0f, 520.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);
}

Brick::~Brick()
= default;


void Brick::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("Brick", x, y, 0, 255, true);
}

void Brick::update()
{
	

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
}

void Brick::clean()
{


}

void Brick::moveLeft()
{
	getRigidBody()->velocity = glm::vec2(-SPEED, 0.0f);
}

void Brick::moveRight()
{
	getRigidBody()->velocity = glm::vec2(SPEED, 0.0f);
}

void Brick::stopMovement()
{
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
}

