#include <vector>
#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>
#include "car.h"
#include "gameplay.h"

bool check_if_out_of_the_screen(Car& other_car)
{
    if (other_car.get_border_top() >= 720)
    {
        return true;
    }

    else return false;
}

void destroy_car(Car& other_car, std::vector<Car>& other_car_vector)
{
    std::swap(other_car, other_car_vector.back());
    other_car_vector.pop_back();
}

bool check_if_overtaken(Car& other_car, Car& xeo)
{
    if (xeo.get_border_bottom() <= other_car.get_border_top())
    {
        return true;
    }

    else return false;
}

bool check_collision(Car& other_car, Car& xeo)
{
    if (xeo.get_border_top() <= other_car.get_border_bottom() &&
        xeo.get_border_bottom() - 24 >= other_car.get_border_top() &&
        xeo.get_border_left() == other_car.get_border_left())
    {
        return true;
    }

    else return false;
}

void set_texture_and_push_back(std::vector<Car>& other_car_vector, std::vector<sf::Texture>& car_texture_vector, std::int8_t& multipler, std::int8_t& theme_id)
{
    if (multipler == 0)
    {
        Car temp_other_car(car_texture_vector[theme_id], multipler, sf::IntRect(0, 0, 48, 96));
        other_car_vector.push_back(temp_other_car);
    }

    else if (multipler == 3)
    {
        Car temp_other_car(car_texture_vector[theme_id], multipler, sf::IntRect(96, 0, 48, 96));
        other_car_vector.push_back(temp_other_car);
    }

    else
    {
        Car temp_other_car(car_texture_vector[theme_id], multipler, sf::IntRect(48, 0, 48, 96));
        other_car_vector.push_back(temp_other_car);
    }
}

void spawn_one_car(std::vector<Car>& other_car_vector, std::vector<sf::Texture>& car_texture_vector, std::int8_t& theme_id)
{
    std::int8_t multipler = rand() % 4;
    set_texture_and_push_back(other_car_vector, car_texture_vector, multipler, theme_id);
}

void spawn_two_cars(std::vector<Car>& other_car_vector, std::vector<sf::Texture>& car_texture_vector, std::int8_t& theme_id)
{
    std::int8_t multipler[2]{ rand() % 4, -1 };

    do
    {
        multipler[1] = rand() % 4;
    } while (multipler[1] == multipler[0]);

    for (std::int8_t i = 0; i < 2; i++)
    {
        set_texture_and_push_back(other_car_vector, car_texture_vector, multipler[i], theme_id);
    }
}

void spawn_three_cars(std::vector<Car>& other_car_vector, std::vector<sf::Texture>& car_texture_vector, std::int8_t& theme_id)
{
    std::int8_t multipler[3]{ rand() % 4, -1, -1 };

    do
    {
        multipler[1] = rand() % 4;
    } while (multipler[1] == multipler[0]);

    do
    {
        multipler[2] = rand() % 4;
    } while (multipler[2] == multipler[1] || multipler[2] == multipler[0]);

    for (std::int8_t i = 0; i < 3; i++)
    {
        set_texture_and_push_back(other_car_vector, car_texture_vector, multipler[i], theme_id);
    }
}

void spawn_other_cars(std::vector<Car>& other_car_vector, std::vector<sf::Texture>& car_texture_vector, std::int8_t& theme_id)
{
    std::int8_t amount = rand() % 9;
    // 0        1 car
    // 1 - 3    2 cars
    // 4 - 8    3 cars

    if (amount >= 4)
    {
        spawn_three_cars(other_car_vector, car_texture_vector, theme_id);
    }

    else if (amount == 0)
    {
        spawn_one_car(other_car_vector, car_texture_vector, theme_id);
    }

    else
    {
        spawn_two_cars(other_car_vector, car_texture_vector, theme_id);
    }
}

void save_best_score(std::string& best_score, std::int8_t& difficulty_level)
{
    std::ofstream file;

    if (difficulty_level == 1)
    {
        file.open("best_score/best_score_1.png");
    }

    else if (difficulty_level == 2)
    {
        file.open("best_score/best_score_2.png");
    }

    else if (difficulty_level == 3)
    {
        file.open("best_score/best_score_3.png");
    }

    else
    {
        std::cout << "\nsomething went really wrong";
    }
    
    if (file.is_open())
    {
        file << best_score + '&';
    }

    else
    {
        std::cout << "\nmissing best_score/best_score_[x].png";
    }

    file.close();
}