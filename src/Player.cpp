#include "Player.h"
#include "TextureManager.h"

Player::Player()
{
	TextureManager::Instance()->load("../Assets/textures/wookie.png", "Wookie");

	getTransform()->position = glm::vec2(400.0f, 500.0f);
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
	getRigidBody()->acceleration = glm::vec2(0.0f, 0.0f);
	getRigidBody()->isColliding = false;
	setType(PLAYER);

	
}

Player::~Player()
= default;

void Player::draw()
{
	// alias for x and y
	const auto x = getTransform()->position.x;
	const auto y = getTransform()->position.y;

	TextureManager::Instance()->draw("Wookie", x, y, 0, 255, true);
	
}

void Player::update()
{
	const float deltaTime = 1.0f / 60.f;

	glm::vec2 pos = getTransform()->position;
	pos.x += getRigidBody()->velocity.x * deltaTime;
	pos.y += getRigidBody()->velocity.y * deltaTime;

	getTransform()->position = pos;
}

void Player::clean()
{

}

void Player::moveLeft() {
	getRigidBody()->velocity = glm::vec2(-SPEED, 0.0f);
}

void Player::moveRight() {
	getRigidBody()->velocity = glm::vec2(SPEED, 0.0f);
}

void Player::moveUp() {
	getRigidBody()->velocity = glm::vec2(0.0f, -SPEED);
}

void Player::moveDown() {
	getRigidBody()->velocity = glm::vec2(0.0f, SPEED);
}

void Player::stopMovement() {
	getRigidBody()->velocity = glm::vec2(0.0f, 0.0f);
}
