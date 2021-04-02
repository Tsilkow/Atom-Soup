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

sf::Vector2f connector(sf::Vector2f a, sf::Vector2f b, sf::FloatRect boundaries, bool wrapping)
{
    if(wrapping) return wrapConnector(a, b, boundaries);
    else return a-b;
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

void printColor(sf::Color toPrint, bool enter)
{
    std::cout << "(" << toPrint.r << ", " << toPrint.g << ", " << toPrint.b << ")";
    if(enter) std::cout << "\n";
}

float modulo(float a, float b)
{
    while(a >= b) a -= b;
    while(a < 0) a += b;

    return a;
}

float quickPower(float base, int power)
{
    if(power == 0) return 1.f;
    if(power == 1) return base;
    if(modulo(power, 2) == 0) return quickPower(base*base, power/2);
    return quickPower(base, power-1)*base;
}

float colorValue(float point)
{
    point = modulo(point, 1.f);
    
    if(point <= 1.f/6.f) return point*6.f;
    if(point <= 3.f/6.f) return 1.f;
    if(point <= 4.f/6.f) return (4.f/6.f - point)*6.f;
    return 0.f;
}

sf::Color colorFromRange(float point)
{
    return sf::Color(std::round(255.f * colorValue(point + 2.f/6.f)),
		     std::round(255.f * colorValue(point          )),
		     std::round(255.f * colorValue(point - 2.f/6.f)));
}

std::vector<sf::Color> generatePalette(int colorTotal)
{
    std::vector<sf::Color> result;

    for(int i = 0; i < colorTotal; ++i)
    {
	result.emplace_back(colorFromRange((float)i/(float)colorTotal));
    }

    return result;
}

std::vector< sf::Vector2f > genCircleShape(float radius, int precision)
{
    std::vector< sf::Vector2f > result;

    for(int i=0; i < precision; ++i)
    {
	result.emplace_back(makeVector(radius, i*2*M_PI/precision));
    }

    return result;
}
