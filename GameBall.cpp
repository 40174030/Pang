#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"

GameBall::GameBall() : 
	_velocity(230.0f), 
	_elapsedTimeSinceStart(0.0f)
{
	Load("images/Ball.png");
	assert(isLoaded());

	getSprite().setOrigin(15, 15);
	setPosition((Game::SCREEN_WIDTH / 2), (Game::SCREEN_HEIGHT / 2) - 15);

	float random_integer = std::rand() % 360 + 1; // Gives random number between 1 and 360.
	_angle = random_integer;
}


GameBall::~GameBall() 
{
}


void GameBall::Update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	// Delay game from starting until 3 seconds have passed
	if (_elapsedTimeSinceStart < 3.0f)
		return;

	float moveAmount = _velocity * elapsedTime;


	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;


	// Collide with the left side of the screen
	if (getPosition().x + moveByX <= 0 + getWidth() / 2 || getPosition().x + getHeight() / 2 + moveByX >= Game::SCREEN_WIDTH)
	{
		// Ricochet!
		_angle = 360.0f - _angle;
		if (_angle > 260.0f && _angle < 280.0f)
			_angle += 20.0f;
		if (_angle > 80.0f && _angle < 100.0f)
			_angle += 20.0f;
		moveByX = -moveByX;
	}

	PlayerPaddle* player1 = dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().get("Paddle1"));
	if (player1 != NULL)
	{
		sf::FloatRect p1BB = player1->getBoundingRect();
		if (p1BB.intersects(getBoundingRect()))
		{		
			_angle = 360.0f - (_angle - 180.0f);
			if (_angle >= 360.0f)
			{
				_angle -= 360.0f;
			}
			moveByY = -moveByY;

			// Make sure ball isn't inside paddle
			if (getBoundingRect().height > player1->getBoundingRect().top)
			{
				setPosition(getPosition().x, player1->getBoundingRect().top - getWidth() / 2 - 1);
			}

			// Now add "English" based on the players velocity.  
			float playerVelocity = player1->getVelocity();

			if (playerVelocity < 0)
			{
				// Moving left
				_angle -= 20.0f;
				if (_angle < 0) 
					_angle = 360.0f - _angle;
			}
			else if (playerVelocity > 0)
			{
				_angle += 20.0f;
				if (_angle > 360.0f) 
					_angle = _angle - 360.0f;
			}

			_velocity += 2.0f;
		}

		// Ball reaches top of screen
		if (getPosition().y - getHeight() / 2 <= 0)
		{
			_angle = 180 - _angle;
			moveByY = -moveByY;
		}

		// Ball reaches bottom of screen
		if (getPosition().y + getHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT)
		{
			GameBall::Reset();
		}
		getSprite().move(moveByX, moveByY);
	}
}

float GameBall::LinearVelocityX(float angle)
{
	angle -= 90;
	if (angle < 0) 
		angle = 360 + angle;
	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

float GameBall::LinearVelocityY(float angle)
{
	angle -= 90;
	if (angle < 0) 
		angle = 360 + angle;
	return (float)std::sin(angle * (3.1415926 / 180.0f));
}

void GameBall::Reset()
{
	// Move to middle of the screen for now and randomize angle
	getSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT / 2);
	_angle = std::rand() % 360 + 1;
	_velocity = 230.0f;
	_elapsedTimeSinceStart = 0.0f;
}