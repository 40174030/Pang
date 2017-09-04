#pragma once
class VisibleGameObject
{
public:
	VisibleGameObject();
	virtual ~VisibleGameObject();

	virtual void Load(std::string filename);
	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(float elapsedTime);

	virtual void setPosition(float x, float y);
	virtual sf::Vector2f getPosition() const;
	virtual bool isLoaded() const;

	virtual float getWidth() const;
	virtual float getHeight() const;

	virtual sf::FloatRect getBoundingRect() const;

protected:
	sf::Sprite& getSprite();

private:
	sf::Sprite _sprite;
	sf::Texture _image;
	std::string _filename;
	bool _isLoaded;
};