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
    sf::Text m_fpsCounter;
    sf::RenderWindow* m_window;
    sf::View m_mainView;
    sf::View m_textView;
    float m_scrollSpeed;
    float m_zoomSpeed;
    int m_ticks;
    
    public:
    Soup(AtomParameters* AParams, sf::RenderWindow* window, sf::Font* font, int atomTotal, sf::FloatRect boundaries);

    bool simulate(bool record=false);
    
    void capture();
    
    void draw(bool record=false);
};
