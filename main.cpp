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

/*
 * to try:
 * randomizing relations distances
 * bigger area (smaller atoms)
 */

using namespace std;

int main()
{
    srand(time(NULL));
        
    AtomParameters AParams =
    {
        generateAtomTypes(10, make_pair(5.f, 5.f), make_pair(2.5f, 5.f), make_pair(10.f, 90.f)),
	1.f,
	1.f,
	0.1f,
	20,
	0.5f,
	false
    };

    AParams.print();
    
    sf::RenderWindow window(sf::VideoMode(800, 800), "Atom Soup");
    window.setFramerateLimit(60);
    sf::View mainView;
    mainView.setCenter(sf::Vector2f(0.f, 0.f));
    mainView.setSize(sf::Vector2f(800.f, 800.f));
    mainView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(mainView);

    Soup soup(&AParams, &window, 200, sf::FloatRect(-400.f, -400.f, 800.f, 800.f));

    soup.simulate();
	
    window.close();
    
    return 0;
}
