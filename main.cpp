#include <iostream>
#include <vector>
#include <fstream>
#include <string>

#include <SFML/Graphics.hpp>
#include "car.h"
#include "road.h"
#include "gui.h"
#include "gameplay.h"

int main()
{
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(1280, 720), "xeo's game beta");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    // score
    std::int32_t score = 0;
    std::string best_score_table[3]
    {
        "0",
        "0",
        "0"
    };

    // difficulty level
    std::int8_t difficulty_level;

    // file with best score
    std::ifstream file;

    for (std::int8_t i = 0; i < 2; i++)
    {
        std::string path = "best_score/best_score_";
        path += std::to_string(i + 1);
        path += ".png";

        file.open(path);

        if (file.is_open())
        {
            std::getline(file, best_score_table[0], '&');
        }

        else
        {
            std::cout << "\nmissing best_score/best_score_" << i + 1 << ".png";
        }

        file.close();
    }

    // fonts
    sf::Font font_regular;
    if (!font_regular.loadFromFile("fonts/RobotoMono-Regular.ttf"))
    {
        std::cout << "\nmissing fonts/RobotoMono-Regular.ttf";
    }

    // colors
    sf::Color theme(255, 0, 255);
    sf::Color theme_transparent(255, 0, 255, 127);
    std::int8_t theme_id = 1;

    // road
    std::vector<sf::Texture> road_texture_vector;

    for (std::int8_t i = 0; i < 7; i++)
    {
        sf::Texture temp_road_texture;
        std::string path = "pics/road/road_";
        path += std::to_string(i);
        path += ".png";

        if (!temp_road_texture.loadFromFile(path))
        {
            std::cout << "\nmissing pics/road/road_[x].png";
        }

        road_texture_vector.push_back(temp_road_texture);
    }

    std::vector<Road> road_vector
    {
        Road(road_texture_vector[theme_id], 503),
        Road(road_texture_vector[theme_id], 560),
        Road(road_texture_vector[theme_id], 575),
        Road(road_texture_vector[theme_id], 632),
        Road(road_texture_vector[theme_id], 647),
        Road(road_texture_vector[theme_id], 704),
        Road(road_texture_vector[theme_id], 719),
        Road(road_texture_vector[theme_id], 776)
    };

    // car's textures
    std::vector<sf::Texture> car_texture_vector;

    for (std::int8_t i = 0; i < 7; i++)
    {
        sf::Texture temp_car_texture;
        std::string path = "pics/car/car_";
        path += std::to_string(i);
        path += ".png";

        if (!temp_car_texture.loadFromFile(path))
        {
            std::cout << "\nmissing pics/car/car_[x].png";
        }

        car_texture_vector.push_back(temp_car_texture);
    }

    // xeo 
    Car xeo(car_texture_vector[theme_id], sf::IntRect(48, 0, 48, 96));
    
    // vector for other cars
    std::vector<Car> other_car_vector;

    // cooldown
    sf::Clock cooldown;
    sf::Time cooldown_duration;

    // screens
    std::int8_t mode = 3;
    // 0    gameplay
    // 1    game over
    // 2    choose level
    // 3    start
    // 4    change theme

    // gui
    std::vector<std::vector<Text_>> gui_vector
    {
        std::vector<Text_>
        {
            Text_("", "", font_regular, 32, sf::Color(theme), 128, 128, false, false),
            Text_("", std::to_string(score), font_regular, 32, sf::Color(theme), 128, 176, false, false)
        },

        std::vector<Text_>
        {
            Text_("game oven", font_regular, 32, sf::Color(theme), 128, 128, false, false),
            Text_("try again", font_regular, 32, sf::Color(theme_transparent), 128, 224, false, true),
            Text_("press t", font_regular, 32, sf::Color(theme), 128, 272, false, false),
            Text_("exit", font_regular, 32, sf::Color(theme_transparent), 128, 368, false, true),
            Text_("press x", font_regular, 32, sf::Color(theme), 128, 416, false, false),
            Text_("change theme", font_regular, 32, sf::Color(theme_transparent), 128, 512, false, true),
            Text_("press c", font_regular, 32, sf::Color(theme), 128, 560, false, false),

            Text_("current score", font_regular, 32, sf::Color(255, 255, 255, 127), 488, 128, true, false),
            Text_("", std::to_string(score), font_regular, 32, sf::Color(255, 255, 255), 488, 176, true, false),
            Text_("best score", font_regular, 32, sf::Color(255, 255, 255, 127), 488, 272, true, false),
            Text_("easy     ", best_score_table[0], font_regular, 32, sf::Color(255, 255, 255), 488, 320, true, false),
            Text_("medium   ", best_score_table[1], font_regular, 32, sf::Color(255, 255, 255), 488, 368, true, false),
            Text_("hart     ", best_score_table[2], font_regular, 32, sf::Color(255, 255, 255), 488, 416, true, false)
        },

        std::vector<Text_>
        {
            Text_("choose difficulty level", "", font_regular, 32, sf::Color(theme), 128, 128, false, false),
            Text_("easy", font_regular, 32, sf::Color(theme_transparent), 128, 224, false, true),
            Text_("press 1", font_regular, 32, sf::Color(theme), 128, 272, false, false),
            Text_("medium", font_regular, 32, sf::Color(theme_transparent), 128, 368, false, true),
            Text_("press 2", font_regular, 32, sf::Color(theme), 128, 416, false, false),
            Text_("hart", font_regular, 32, sf::Color(theme_transparent), 128, 512, false, true),
            Text_("press 3", font_regular, 32, sf::Color(theme), 128, 560, false, false)
        },

        std::vector<Text_>
        {
            Text_("xeo's game beta", font_regular, 32, sf::Color(theme), 128, 128, false, false),
            Text_("start", font_regular, 32, sf::Color(theme_transparent), 128, 224, false, true),
            Text_("press s", font_regular, 32, sf::Color(theme), 128, 272, false, true),
        },

        std::vector<Text_>
        {
            Text_("change theme", "", font_regular, 32, sf::Color(theme), 128, 128, false, false),
            Text_("cyan", font_regular, 32, sf::Color(0, 255, 255, 127), 128, 224, true, false),
            Text_("press 1", font_regular, 32, sf::Color(0, 255, 255), 128, 272, true, false),
            Text_("magenta [def]", font_regular, 32, sf::Color(255, 0, 255, 127), 128, 368, true, false),
            Text_("press 2", font_regular, 32, sf::Color(255, 0, 255), 128, 416, true, false),
            Text_("yellow", font_regular, 32, sf::Color(255, 255, 0, 127), 128, 512, true, false),
            Text_("press 3", font_regular, 32, sf::Color(255, 255, 0), 128, 560, true, false),

            Text_("red", font_regular, 32, sf::Color(255, 0, 0, 127), 488, 128, true, false),
            Text_("press 4", font_regular, 32, sf::Color(255, 0, 0), 488, 176, true, false),
            Text_("green", font_regular, 32, sf::Color(0, 255, 0, 127), 488, 272, true, false),
            Text_("press 5", font_regular, 32, sf::Color(0, 255, 0), 488, 320, true, false),
            Text_("blue", font_regular, 32, sf::Color(0, 0, 255, 127), 488, 416, true, false),
            Text_("press 6", font_regular, 32, sf::Color(0, 0, 255), 488, 464, true, false),
            Text_("black [experimental]", font_regular, 32, sf::Color(255, 255, 255, 127), 488, 560, true, false),
            Text_("press 7", font_regular, 32, sf::Color(255, 255, 255), 488, 608, true, false),

            Text_("back", font_regular, 32, sf::Color(theme_transparent), 848, 128, false, false),
            Text_("press b", font_regular, 32, sf::Color(theme), 848, 176, false, false)
        },
    };

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.key.code == sf::Keyboard::X)
            {
                window.close();
            }

            switch (mode)
            {
            case 0:
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::D)
                    {
                        xeo.move_right(car_texture_vector, 72, theme_id);
                    }

                    if (event.key.code == sf::Keyboard::A)
                    {
                        xeo.move_left(car_texture_vector, 72, theme_id);
                    }
                }

                break;

            case 1:
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::T)
                    {
                        mode = 2;
                    }
                }

                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::C)
                    {
                        mode = 4;
                    }
                }

                break;

            case 2:
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1)
                    {
                        difficulty_level = 1;
                        gui_vector[2][0].change_label("easy");
                        road_update(road_vector, road_texture_vector, theme_id);
                        xeo.change_texture(car_texture_vector[theme_id]);
                        mode = 0;
                    }

                    if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2)
                    {
                        difficulty_level = 2;
                        gui_vector[2][0].change_label("medium");
                        road_update(road_vector, road_texture_vector, theme_id);
                        xeo.change_texture(car_texture_vector[theme_id]);
                        mode = 0;
                    }

                    if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3)
                    {
                        difficulty_level = 3;
                        gui_vector[2][0].change_label("hart");
                        road_update(road_vector, road_texture_vector, theme_id);
                        xeo.change_texture(car_texture_vector[theme_id]);
                        mode = 0;
                    }
                }

                break;

            case 3:
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::S)
                    {
                        mode = 2;
                    }
                }

                break;

            case 4:
                if (event.type == sf::Event::KeyPressed)
                {
                    if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1)
                    {
                        theme = sf::Color(0, 255, 255);
                        theme_transparent = sf::Color(0, 255, 255, 127);
                        theme_id = 0;
                        gui_update(gui_vector, theme, theme_transparent);
                        mode = 1;
                    }

                    if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2)
                    {
                        theme = sf::Color(255, 0, 255);
                        theme_transparent = sf::Color(255, 0, 255, 127);
                        theme_id = 1;
                        gui_update(gui_vector, theme, theme_transparent);
                        mode = 1;
                    }

                    if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3)
                    {
                        theme = sf::Color(255, 255, 0);
                        theme_transparent = sf::Color(255, 255, 0, 127);
                        theme_id = 2;
                        gui_update(gui_vector, theme, theme_transparent);
                        mode = 1;
                    }

                    if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4)
                    {
                        theme = sf::Color(255, 0, 0);
                        theme_transparent = sf::Color(255, 0, 0, 127);
                        theme_id = 3;
                        gui_update(gui_vector, theme, theme_transparent);
                        mode = 1;
                    }

                    if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5)
                    {
                        theme = sf::Color(0, 255, 0);
                        theme_transparent = sf::Color(0, 255, 0, 127);
                        theme_id = 4;
                        gui_update(gui_vector, theme, theme_transparent);
                        mode = 1;
                    }

                    if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6)
                    {
                        theme = sf::Color(0, 0, 255);
                        theme_transparent = sf::Color(0, 0, 255, 127);
                        theme_id = 5;
                        gui_update(gui_vector, theme, theme_transparent);
                        mode = 1;
                    }

                    if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7)
                    {
                        theme = sf::Color(7, 7, 7);
                        theme_transparent = sf::Color(7, 7, 7, 127);
                        theme_id = 6;
                        gui_update(gui_vector, theme, theme_transparent);
                        mode = 1;
                    }

                    if (event.key.code == sf::Keyboard::B)
                    {
                        mode = 1;
                    }
                }
            }
        }

        window.clear();

        switch (mode)
        {
        case 0:
            if (cooldown.getElapsedTime() >= cooldown_duration)
            {
                cooldown_duration = sf::milliseconds(1000 - (difficulty_level - 1) * 200);
                cooldown.restart();
                spawn_other_cars(other_car_vector, car_texture_vector, theme_id);
            }

            for (std::int8_t i = 0; i < other_car_vector.size(); i++)
            {
                if (check_if_overtaken(other_car_vector[i], xeo))
                {
                    if (other_car_vector[i].is_reward_available)
                    {
                        other_car_vector[i].is_reward_available = false;
                        score += 10;
                    }
                }
                
                if (check_collision(other_car_vector[i], xeo))
                {
                    other_car_vector.clear();

                    if (difficulty_level == 1)
                    {
                        gui_vector[1][8].change_label("easy     ");
                    }

                    else if (difficulty_level == 2)
                    {
                        gui_vector[1][8].change_label("medium   ");
                    }

                    else if (difficulty_level == 3)
                    {
                        gui_vector[1][8].change_label("hart     ");
                    }

                    else
                    {
                        std::cout << "\nsomething went really wrong";
                    }

                    if (score <= std::stoi(best_score_table[difficulty_level - 1]))
                    {
                        gui_vector[1][8].change_content(std::to_string(score));
                    }

                    else if (score > std::stoi(best_score_table[difficulty_level - 1]))
                    {
                        gui_vector[1][8].change_content(std::to_string(score) + " [best]");
                        best_score_table[difficulty_level - 1] = std::to_string(score);
                        save_best_score(best_score_table[difficulty_level - 1], difficulty_level);
                        gui_vector[1][9 + difficulty_level].change_content(best_score_table[difficulty_level - 1]);
                    }

                    score = 0;
                    mode = 1;
                    break;
                }

                other_car_vector[i].move(8 + (difficulty_level - 1) * 2);
                other_car_vector[i].draw(window);
            }

            for (std::int8_t i = 0; i < other_car_vector.size(); i++)
            {
                if (check_if_out_of_the_screen(other_car_vector[i]))
                {
                    destroy_car(other_car_vector[i], other_car_vector);
                }
            }


            for (std::int8_t i = 0; i < road_vector.size(); i++)
            {
                road_vector[i].draw(window);
            }

            gui_vector[0][1].change_content(std::to_string(score));
            
            for (std::int8_t i = 0; i < gui_vector[0].size(); i++)
            {
                gui_vector[0][i].draw(window);
            }

            xeo.draw(window);

            break;

        case 1:
            for (std::int8_t i = 0; i < gui_vector[1].size(); i++)
            {
                gui_vector[1][i].draw(window);
            }

            break;

        case 2:
            for (std::int8_t i = 0; i < gui_vector[2].size(); i++)
            {
                gui_vector[2][i].draw(window);
            }

            break;

        case 3:
            for (std::int8_t i = 0; i < gui_vector[3].size(); i++)
            {
                gui_vector[3][i].draw(window);
            }

            break;

        case 4:
            for (std::int8_t i = 0; i < gui_vector[4].size(); i++)
            {
                gui_vector[4][i].draw(window);
            }

            break;
        }

        window.display();
    }

    return 0;
}