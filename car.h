#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class Car
{
public:
	bool is_reward_available = true;

	Car(sf::Texture& texture, sf::IntRect intrect);

	Car(sf::Texture& texture, float multipler, sf::IntRect intrect);

	void move(std::int8_t speed);

	void move_right(std::vector<sf::Texture>& texture_vector, float speed, std::int8_t theme_id);

	void move_left(std::vector<sf::Texture>& texture_vector, float speed, std::int8_t theme_id);

	float get_border_top();

	float get_border_right();

	float get_border_bottom();

	float get_border_left();

	void change_texture(sf::Texture& texture);

	void draw(sf::RenderWindow& window);

	~Car();

private:
	sf::Sprite body;
	sf::Texture texture;
};