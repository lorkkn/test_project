#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <cmath>

#define playerSize 50

void onResize(sf::RenderWindow& window);

void PlayerMovement(sf::RenderWindow& window, sf::RectangleShape& player);

int getRandomNumber(int min, int max);


