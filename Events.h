#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <cmath>
#include "Classes.h"

#define playerSize 50

void onResize(sf::RenderWindow& window);

void PlayerMovement(sf::RenderWindow& window, sf::RectangleShape& player);

void Shooting(Player player, std::vector<Bullet>& bullets, sf::Clock& bullet_clock, float freq);

int getRandomNumber(int min, int max);


