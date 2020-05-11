#pragma once

#include <vector>

#include <SFML/Graphics.hpp>
#include "car.h"

bool check_if_out_of_the_screen(Car& other_car);

void destroy_car(Car& other_car, std::vector<Car>& other_car_vector);

bool check_if_overtaken(Car& other_car, Car& xeo);

bool check_collision(Car& other_car, Car& xeo);

void spawn_other_cars(std::vector<Car>& other_car_vector, std::vector<sf::Texture>& car_texture_vector, std::int8_t& theme_id);

void save_best_score(std::string& best_score, std::int8_t& difficulty_level);