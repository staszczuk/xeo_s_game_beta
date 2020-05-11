#pragma once

#include <SFML/Graphics.hpp>

class Road
{
public:
    Road(sf::Texture& texture, std::int16_t x);

    void change_texture(std::vector<sf::Texture>& road_texture_vector, std::int8_t& theme_id);

    void draw(sf::RenderWindow& window);

    ~Road();

private:
    sf::Sprite body;
};

void road_update(std::vector<Road>& road_vector, std::vector<sf::Texture>& road_texture_vector, std::int8_t& theme_id);