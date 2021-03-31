#include "commons.hpp"


float length(sf::Vector2f a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}

int RandomI(int min, int max)
{
    if(min >= max) return min;
    else return rand() % (max-min+1) + min;
}

float RandomF(float min, float max, float step)
{
    return RandomI((int)std::round(min/step), (int)std::round(max/step)) * step;
}

sf::Vector2f makeVector(float length, float angle)
{
    return sf::Vector2f(length * cos(angle), length * sin(angle));
}

sf::Vector2f Random2f(float lengthMin, float lengthMax, float lengthStep)
{
    return makeVector(RandomF(lengthMin, lengthMax, lengthStep), RandomF(0, 2*M_PI));
}

sf::Vector2f Random2f(sf::FloatRect boundaries)
{
    return sf::Vector2f(boundaries.left + RandomF(0.f, boundaries.width ),
			boundaries.top  + RandomF(0.f, boundaries.height));
}

void printVector(sf::Vector2f a, bool enter)
{
    std::cout << "( " << a.x << ", " << a.y << ") ";
    if(enter) std::cout << "\n";
}

// vector from b to a
sf::Vector2f wrapConnector(sf::Vector2f a, sf::Vector2f b, sf::FloatRect boundaries)
{
    if(fabs(a.x - b.x) > boundaries.width/2)
    {
	if(a.x > b.x) a.x -= boundaries.width;
	else a.x += boundaries.width;
    }
    if(fabs(a.y - b.y) > boundaries.height/2)
    {
	if(a.y > b.y) a.y -= boundaries.height;
	else a.y += boundaries.height;
    }
    
    return a-b;
}
