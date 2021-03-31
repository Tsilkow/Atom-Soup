// Tsilkow

#include <iostream>
#include <vector>
#include <time.h>
#include <memory>
#include <math.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include "commons.hpp"
#include "atom.hpp"


using namespace std;

int main()
{
    std::vector< AtomType > atomTypes;
    atomTypes.push_back(
	   {
	       1.f,
	       1.f,
	       sf::Color(255, 128,   0),
	       {{1.f, 0.f}, {0.f, 1.f}, {-1.f, 0.f}, {0.f, -1.f}},
	       {1, 0, -1}
	   });
    atomTypes.push_back(
	   {
	       1.f,
	       1.f,
	       sf::Color(  0, 255,   0),
	       {{1.f, 0.f}, {0.f, 1.f}, {-1.f, 0.f}, {0.f, -1.f}},
	       {0, 1, 0}
	   });
    atomTypes.push_back(
	   {
	       1.f,
	       1.f,
	       sf::Color(255,   0, 255),
	       {{1.f, 0.f}, {0.f, 1.f}, {-1.f, 0.f}, {0.f, -1.f}},
	       {-1, -1, -1}
	   });
    
    AtomParameters AParams =
    {
	atomTypes,
	100,
	10
    };
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "Atom Soup");
    window.setFramerateLimit(60);

    
	
    window.close();
    
    return 0;
}
