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

#include "commons.hpp"
#include "atom.hpp"


class Soup
{
    private:
    AtomParameters* m_AParams;
    std::vector< Atom > m_atoms;
    sf::FloatRect m_boundaries;
    std::vector< sf::Vertex > m_boundRepres;
    sf::RenderWindow* m_window;
    sf::View m_view;
    float m_scrollSpeed;
    float m_zoomSpeed;
    
    public:
    Soup(AtomParameters* AParams, sf::RenderWindow* window, int atomTotal, sf::FloatRect boundaries);

    bool simulate();
    
    void draw();
};
