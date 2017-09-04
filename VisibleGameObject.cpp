#include "stdafx.h"
#include "VisibleGameObject.h"

VisibleGameObject::VisibleGameObject() : _isLoaded(false) {}

VisibleGameObject::~VisibleGameObject() {}

void VisibleGameObject::Load(std::string filename)
{
	if (_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_image);
		_isLoaded = true;
	}
}

void VisibleGameObject::Draw(sf::RenderWindow& renderWindow)
{
	if (_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}

void VisibleGameObject::Update(float elapsedTime) {}

void VisibleGameObject::setPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}

sf::Vector2f VisibleGameObject::getPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

sf::Sprite& VisibleGameObject::getSprite()
{
	return _sprite;
}

bool VisibleGameObject::isLoaded() const
{
	return _isLoaded;
}

float VisibleGameObject::getHeight() const
{
	return _sprite.getLocalBounds().height;
}

float VisibleGameObject::getWidth() const
{
	return _sprite.getLocalBounds().width;
}

sf::FloatRect VisibleGameObject::getBoundingRect() const
{
	sf::FloatRect size = _sprite.getLocalBounds();
	sf::Vector2f position = _sprite.getPosition();

	return sf::FloatRect(position.x - size.width / 2, 
						 position.y - size.height / 2, 
						 position.x + size.width / 2, 
						 position.y + size.height / 2);
}