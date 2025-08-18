#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <cmath>
#include "Classes.h"

#define playerSize 50

void onResize(sf::RenderWindow& window);

void PlayerMovement(sf::RenderWindow& window, sf::RectangleShape& player);

void Shooting(Player player, std::vector<Bullet>& bullets, sf::Clock &bullet_clock);

void EnemyMovement(sf::RenderWindow& window, Player& player, std::vector<Enemy>& enemies);

int getRandomNumber(int min, int max);

void EnemySpawn(sf::RenderWindow& window, Player& player, std::vector<Enemy>& enemies);


