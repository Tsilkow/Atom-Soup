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
 * 1617963337
 * 1617967701
 * 1617968058
 */

using namespace std;

int main(int argc, char* argv[])
{
    int seed = time(NULL);
    if(argc > 1) seed = atoi(argv[1]);
    srand(seed);
    cout << seed << endl;
        
    AtomParameters AParams =
    {
        generateAtomTypes(4, make_pair(5.f, 5.f), make_pair(5.f, 5.f), make_pair(10.f, 100.f)),
	1.f,  // peakRelStr
	2.f,  // peakRepStr
	0.2f, // friction
	20,   // trailLength
	0.5f, // bounce
        true // wrapping
    };

    AParams.print();

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow window(sf::VideoMode(800, 800), "Atom Soup", sf::Style::Default, settings);
    window.setFramerateLimit(60);
    sf::View mainView;
    mainView.setCenter(sf::Vector2f(0.f, 0.f));
    mainView.setSize(sf::Vector2f(800.f, 800.f));
    mainView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    window.setView(mainView);
    sf::Font font;
    if(!font.loadFromFile("data/Anonymous.ttf"))
    {
	std::cout << "!ERROR! Couldn't load the font! Aborting ...\n";
	return 1;
    }

    Soup soup(&AParams, &window, &font, 200, sf::FloatRect(-400.f, -400.f, 800.f, 800.f));

    soup.simulate(false);
	
    window.close();
    
    return 0;
}
