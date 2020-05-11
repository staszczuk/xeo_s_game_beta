#include <SFML/Graphics.hpp>
#include "road.h"

Road::Road(sf::Texture& texture, std::int16_t x)
{
    body.setScale(1, 1);
    body.setTexture(texture);
    body.setPosition(x, 0);
    body.setOrigin(0, 0);
}

void Road::change_texture(std::vector<sf::Texture>& road_texture_vector, std::int8_t& theme_id)
{
    Road::body.setTexture(road_texture_vector[theme_id]);
}

void Road::draw(sf::RenderWindow& window)
{
    window.draw(body);
}

Road::~Road() {}

void road_update(std::vector<Road>& road_vector, std::vector<sf::Texture>& road_texture_vector, std::int8_t& theme_id)
{
		for (std::int8_t i = 0; i < road_vector.size(); i++)
		{
            road_vector[i].change_texture(road_texture_vector, theme_id);
		}
}