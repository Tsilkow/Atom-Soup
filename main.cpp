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
#include "soup.hpp"


using namespace std;

int main()
{
    srand(time(NULL));
    
    std::vector< AtomType > atomTypes;
    atomTypes.push_back(
	   {
	       10.f,
	       1.f,
	       sf::Color(255, 128,   0),
	       {{10.f, 0.f}, {0.f, 10.f}, {-10.f, 0.f}, {0.f, -10.f}},
	       {1, 0, -1}
	   });
    atomTypes.push_back(
	   {
	       10.f,
	       1.f,
	       sf::Color(  0, 255,   0),
	       {{10.f, 0.f}, {0.f, 10.f}, {-10.f, 0.f}, {0.f, -10.f}},
	       {0, 1, 0}
	   });
    atomTypes.push_back(
	   {
	       10.f,
	       1.f,
	       sf::Color(255,   0, 255),
	       {{10.f, 0.f}, {0.f, 10.f}, {-10.f, 0.f}, {0.f, -10.f}},
	       {-1, -1, -1}
	   });
    
    AtomParameters AParams =
    {
	atomTypes,
	50.f,
	1.f
    };
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "Atom Soup");
    window.setFramerateLimit(60);
    sf::View mainView;
    mainView.setCenter(sf::Vector2f(0.f, 0.f));
    mainView.setSize(sf::Vector2f(800.f, 800.f));
    mainView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(mainView);

    Soup soup(&AParams, &window, 20, sf::FloatRect(-400.f, -400.f, 800.f, 800.f));

    soup.simulate();
	
    window.close();
    
    return 0;
}
