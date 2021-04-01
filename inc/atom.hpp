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


struct Relation
{
    int sign; // -1 = repulsion, 0 = neutral, 1 = attraction
    float maxDistance;  // maximal relation distance - how far away can two atoms be to still affect each other
};

struct AtomType
{
    float size;
    float weight;
    sf::Color color;
    std::vector< sf::Vector2f > shape;
    std::vector< Relation > relations;
};

struct AtomParameters
{
    std::vector< AtomType > types;
    float peakRelStr; // peak relation strength - greatest strength the relation between two atoms can exert
    float peakRepStr; // peak repel strength
    float friction;
    int trailLength;
    
    void print();
};

std::vector< AtomType > generateAtomTypes
(int typeTotal, pairF sizeRange, pairF weightRange, pairF maxDistanceRange);

class Atom
{
    private:
    AtomParameters* m_parameters;
    int m_type;
    sf::Vector2f m_position;
    sf::Vector2f m_velocity;
    sf::Vector2f m_force;
    std::vector< sf::Vertex > m_representation;
    std::vector< std::vector< sf::Vertex > > m_trail;

    float calcRepelStr(float distance);
	
    float calcRelStr(float distance, int targetType);

    public:
    Atom(AtomParameters* parameters, int type, sf::Vector2f startPosition, sf::Vector2f startVelocity);

    void addForce(sf::Vector2f force);
    
    sf::Vector2f exertForce(int targetType, sf::Vector2f distance);

    void tick(sf::FloatRect boundaries);
    
    void draw(sf::RenderTarget& target);


    const int& getType() const {return m_type; }
    const sf::Vector2f& getPosition() const {return m_position; }
};
