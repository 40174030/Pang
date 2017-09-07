#pragma once
#include "VisibleGameObject.h"

class PlayerPaddle : public VisibleGameObject
{
public:
	PlayerPaddle();
	~PlayerPaddle();

	void Update(float elapsedTime);
	void Draw(sf::RenderWindow& rw);
	void Reset();

	float getVelocity() const;

private:
	float _velocity;
	float _maxVelocity;
};
