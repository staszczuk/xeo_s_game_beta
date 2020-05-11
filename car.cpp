#include <vector>

#include <SFML/Graphics.hpp>
#include "car.h"

Car::Car(sf::Texture& texture, sf::IntRect intrect)
{
	Car::texture = texture;
	Car::body.setScale(1, 1);
	Car::body.setTextureRect(intrect);
	Car::body.setTexture(Car::texture);
	Car::body.setPosition(580, 528);
}

Car::Car(sf::Texture& texture, float multipler, sf::IntRect intrect)
{
	Car::body.setScale(1, 1);
	Car::body.setTextureRect(intrect);
	Car::body.setTexture(texture);
	Car::body.setPosition(508 + 72 * multipler, -96);
}

void Car::move(std::int8_t speed)
{
	Car::body.move(0, speed);
}

void Car::move_right(std::vector<sf::Texture>& texture_vector, float speed, std::int8_t theme_id)
{
	if (Car::body.getPosition().x == 508)
	{
		Car::body.move(speed, 0);
		Car::body.setTextureRect(sf::IntRect(48, 0, 48, 96));
		Car::body.setTexture(texture_vector[theme_id]);
	}

	else if (Car::body.getPosition().x == 580)
	{
		Car::body.move(speed, 0);
		Car::body.setTextureRect(sf::IntRect(48, 0, 48, 96));
		Car::body.setTexture(texture_vector[theme_id]);
	}

	else if (Car::body.getPosition().x == 652)
	{
		Car::body.move(speed, 0);
		Car::body.setTextureRect(sf::IntRect(96, 0, 48, 96));
		Car::body.setTexture(texture_vector[theme_id]);
	}

	else if (Car::body.getPosition().x == 724)
	{
		Car::body.setPosition(508, 528);
		Car::body.setTextureRect(sf::IntRect(0, 0, 48, 96));
		Car::body.setTexture(texture_vector[theme_id]);
	}
}

void Car::move_left(std::vector<sf::Texture>& texture_vector, float speed, std::int8_t theme_id)
{
	if (Car::body.getPosition().x == 508)
	{
		Car::body.setPosition(724, 528);
		Car::body.setTextureRect(sf::IntRect(96, 0, 48, 96));
		Car::body.setTexture(texture_vector[theme_id]);
	}

	else if (Car::body.getPosition().x == 580)
	{
		Car::body.move(-speed, 0);
		Car::body.setTextureRect(sf::IntRect(0, 0, 48, 96));
		Car::body.setTexture(texture_vector[theme_id]);
	}

	else if (Car::body.getPosition().x == 652)
	{
		Car::body.move(-speed, 0);
		Car::body.setTextureRect(sf::IntRect(48, 0, 48, 96));
		Car::body.setTexture(texture_vector[theme_id]);
	}

	else if (Car::body.getPosition().x == 724)
	{
		Car::body.move(-speed, 0);
		Car::body.setTextureRect(sf::IntRect(48, 0, 48, 96));
		Car::body.setTexture(texture_vector[theme_id]);
	}
}

float Car::get_border_top()
{
	return Car::body.getGlobalBounds().top;
}

float Car::get_border_right()
{
	return Car::body.getGlobalBounds().left + Car::body.getGlobalBounds().width;
}

float Car::get_border_bottom()
{
	return Car::body.getGlobalBounds().top + Car::body.getGlobalBounds().height;
}

float Car::get_border_left()
{
	return Car::body.getGlobalBounds().left;
}

void Car::change_texture(sf::Texture& texture)
{
	Car::texture = texture;
	Car::body.setTexture(Car::texture);
}

void Car::draw(sf::RenderWindow& window)
{
	window.draw(Car::body);
}

Car::~Car() {}