#include <SFML/Graphics.hpp>
#include "gui.h"

Text_::Text_(std::string label, std::string content, sf::Font& font, std::int8_t size, sf::Color color, float x, float y, bool protected_, bool theme_semi_transparent)
{
	Text_::color = color;
	Text_::label = label;
	Text_::content = content;
	Text_::protected_ = protected_;
	Text_::theme_semi_transparent = theme_semi_transparent;
	Text_::body.setString(Text_::label + Text_::content);
	Text_::body.setFont(font);
	Text_::body.setCharacterSize(size);
	Text_::body.setFillColor(Text_::color);
	Text_::body.setPosition(x, y);
	Text_::body.setStyle(sf::Text::Regular);
}

Text_::Text_(std::string label, sf::Font& font, std::int8_t size, sf::Color color, float x, float y, bool protected_, bool theme_semi_transparent)
{
	Text_::color = color;
	Text_::label = label;
	Text_::protected_ = protected_;
	Text_::theme_semi_transparent = theme_semi_transparent;
	Text_::body.setString(Text_::label);
	Text_::body.setFont(font);
	Text_::body.setCharacterSize(size);
	Text_::body.setFillColor(Text_::color);
	Text_::body.setPosition(x, y);
	Text_::body.setStyle(sf::Text::Regular);
}

void Text_::change_label(std::string label)
{
	Text_::label = label;
	Text_::body.setString(Text_::label + Text_::content);
}

void Text_::change_content(std::string content)
{
	Text_::content = content;
	Text_::body.setString(Text_::label + Text_::content);
}

void Text_::change_color(sf::Color& theme_solid, sf::Color& theme_semi_transparent)
{
	if (!Text_::protected_)
	{
		if (!Text_::theme_semi_transparent)
		{
			Text_::color = theme_solid;
			Text_::body.setFillColor(theme_solid);
		}
		
		else
		{
			Text_::color = theme_semi_transparent;
			Text_::body.setFillColor(theme_semi_transparent);
		}
	}
}

void Text_::draw(sf::RenderWindow& window)
{
	window.draw(Text_::body);
}

Text_::~Text_() {}

void gui_update(std::vector<std::vector<Text_>>& gui_vector, sf::Color& theme_solid, sf::Color& theme_semi_transparent)
{
	for (std::int8_t i = 0; i < gui_vector.size(); i++)
	{
		for (std::int8_t j = 0; j < gui_vector[i].size(); j++)
		{
			gui_vector[i][j].change_color(theme_solid, theme_semi_transparent);
		}
	}
}