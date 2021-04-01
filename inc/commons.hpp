#pragma once

#include <iostream>
#include <vector>
#include <time.h>
#include <memory>
#include <math.h>
#include <utility>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>


typedef std::pair<int, int> pairI;
typedef std::pair<float, float> pairF;

float length(sf::Vector2f a);

int RandomI(int min, int max);

inline int RandomI(pairI range) {return RandomI(range.first, range.second); }

float RandomF(float min, float max, float step=0.01f);

inline float RandomF(pairF range) {return RandomF(range.first, range.second); }

sf::Vector2f makeVector(float length, float angle);

sf::Vector2f Random2f(float lengthMin, float lengthMax, float lengthStep);

sf::Vector2f Random2f(sf::FloatRect boundaries);

void printVector(sf::Vector2f a, bool enter=true);

sf::Vector2f wrapConnector(sf::Vector2f a, sf::Vector2f b, sf::FloatRect boundaries);

float modulo(float a, float b);

void printColor(sf::Color toPrint, bool enter=true);

float colorValue(float point);

sf::Color colorFromRange(float point);

std::vector<sf::Color> generatePalette(int colorTotal);

std::vector< sf::Vector2f > genCircleShape(float radius, int precision=32);
