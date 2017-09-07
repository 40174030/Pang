#pragma once
#include "VisibleGameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
	int getObjectCount() const;
	VisibleGameObject* get(std::string name) const;

	void drawAll(sf::RenderWindow& renderWindow);
	void updateAll();
	void resetAll();

	sf::Clock& getClock();

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;

	sf::Clock clock;

	struct GameObjectDeallocator
	{
		void operator()(const std::pair<std::string, VisibleGameObject*>& p) const
		{
			delete p.second;
		}
	};
};