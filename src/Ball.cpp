#include "Ball.h"
#include "TextureManager.h"

Ball::Ball()
{
	TextureManager::Instance()->load("../Assets/textures/Ball.png", "Ball");

	getTransform()->position = glm::vec2(400.0f, 200.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 20.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;

}


Ball::~Ball()
= default;


void Ball::draw()
{
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("Ball", x, y, 0, 255, true);

}

void Ball::update()
{
	getRigidBody()->velocity += (getRigidBody()->acceleration + gravity) * deltaTime;
	getTransform()->position += getRigidBody()->velocity * deltaTime;
}


void Ball::clean()
{

}