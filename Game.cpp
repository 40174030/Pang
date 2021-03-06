#include "stdafx.h"
#include "Game.h"
#include "MainMenu.h"
#include "SplashScreen.h"

void Game::Start()
{
	if (_gameState != Uninitialized)
		return;

	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "Pang!");

	PlayerPaddle* player1 = new PlayerPaddle();

	GameBall* ball = new GameBall();

	_gameObjectManager.Add("Paddle1", player1);
	_gameObjectManager.Add("Ball", ball);
	_gameState = Game::ShowingSplash;

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}

const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return Game::_gameObjectManager;
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);

		switch (_gameState)
		{
		case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
		case Game::ShowingMenu:
		{
			ShowMenu();
			_gameObjectManager.resetAll();
			break;
		}
		case Game::Playing:
		{

			_mainWindow.clear(sf::Color(255, 0, 0));
			_gameObjectManager.updateAll();
			_gameObjectManager.drawAll(_mainWindow);

			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed)
				_gameState = Game::Exiting;
			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape)
					_gameState = Game::ShowingMenu;
			}
			break;
		}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	_gameObjectManager.getClock().restart();

	switch (result)
	{
	case MainMenu::Exit:
	{
		_gameState = Game::Exiting;
		break;
	}
	case MainMenu::Play:
	{
		_gameState = Game::Playing;
		break;
	}
	}
}

Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;