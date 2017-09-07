#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

PlayerPaddle::PlayerPaddle() : _velocity(0), _maxVelocity(600.0f) 
{
	Load("images/Paddle.png");
	assert(isLoaded());

	getSprite().setOrigin(getSprite().getLocalBounds().width / 2, getSprite().getLocalBounds().height / 2);
	setPosition((SCREEN_WIDTH / 2) - 45, 700);
}

PlayerPaddle::~PlayerPaddle() {}

void PlayerPaddle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

void PlayerPaddle::Reset()
{
	
}

float PlayerPaddle::getVelocity() const
{
	return _velocity;
}

void PlayerPaddle::Update(float elapsedTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity -= 3.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity += 3.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity = 0.0f;
	}
	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;
	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	sf::Vector2f pos = this->getPosition();

	if (pos.x < getSprite().getLocalBounds().width / 2
		|| pos.x >(Game::SCREEN_WIDTH - getSprite().getLocalBounds().width / 2))
	{
		_velocity = -_velocity; // Bounce by current velocity in opposite direction
	}

	getSprite().move(_velocity * elapsedTime, 0);
}