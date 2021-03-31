#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <memory>
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


float length(sf::Vector2f a);

int RandomI(int min, int max);

float RandomF(float min, float max, float step=0.01f);

sf::Vector2f makeVector(float length, float angle);

sf::Vector2f Random2f(float lengthMin, float lengthMax, float lengthStep);

sf::Vector2f Random2f(sf::FloatRect boundaries);

void printVector(sf::Vector2f a, bool enter=true);

sf::Vector2f wrapConnector(sf::Vector2f a, sf::Vector2f b, sf::FloatRect boundaries);
