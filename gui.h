#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

class Text_
{
public:
	Text_(std::string label, std::string content, sf::Font& font, std::int8_t size, sf::Color color, float x, float y, bool protected_, bool theme_semi_transparent);
	
	Text_(std::string label, sf::Font& font, std::int8_t size, sf::Color color, float x, float y, bool protected_, bool theme_semi_transparent);

	void change_label(std::string label);

	void change_content(std::string content);

	void change_color(sf::Color& theme_solid, sf::Color& theme_semi_transparent);

	void draw(sf::RenderWindow& window);

	~Text_();

private:
	sf::Text body;
	sf::Color color;
	std::string label;
	std::string content;
	bool protected_;
	bool theme_semi_transparent;
};

void gui_update(std::vector<std::vector<Text_>>& gui_vector, sf::Color& theme_solid, sf::Color& theme_semi_transparent);