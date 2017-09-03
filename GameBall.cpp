#include "stdafx.h"
#include "GameBall.h"


GameBall::GameBall()
{
	Load("images/Ball.png");
	assert(isLoaded());

	getSprite().setOrigin(15, 15);
}


GameBall::~GameBall() {}