#include "atom.hpp"


Atom::Atom(AtomParameters* parameters, int type, sf::Vector2f startPosition, sf::Vector2f startVelocity):
    m_parameters(parameters),
    m_type(type),
    m_position(startPosition),
    m_velocity(startVelocity),
    m_force(0.f, 0.f)
{
    printVector(startPosition);
    m_representation.emplace_back(m_position, m_parameters->types[m_type].color);
    for(auto &v: m_parameters->types[m_type].shape)
    {
	m_representation.emplace_back(v + m_position, m_parameters->types[m_type].color);
    }
    m_representation.emplace_back(m_parameters->types[m_type].shape[0] + m_position,
				  m_parameters->types[m_type].color);
}

void Atom::addForce(sf::Vector2f force)
{
    m_force += force;
}

float Atom::calcRepelStr(float distance)
{
    float size = m_parameters->types[m_type].size;
    return 1.f/((distance - size)/size);
}

float Atom::calcRelStr(float distance)
{
    float size = m_parameters->types[m_type].size;
    float maxDist = m_parameters->maxRelDist;

    return std::max(0.f,
		    m_parameters->peakRelStr * (1 - 2.f/(maxDist - size) *
						std::fabs(distance - (maxDist + size)/2.f)));
}

sf::Vector2f Atom::exertForce(int targetType, sf::Vector2f connector)
{
    float distance = length(connector);
    // if the atoms are overlapping, they're always repelling
    if(distance < m_parameters->types[m_type].size)
    {
	return calcRepelStr(distance) * connector/distance * -1.f;
    }
    else
    {
	int relType = m_parameters->types[m_type].relations[targetType];
	// if relation is neutral
	if(relType == 0) return sf::Vector2f(0.f, 0.f);
	else
	{
	    return calcRelStr(distance) * connector/distance * ((float)relType);
	}
    }
}

void Atom::tick(sf::FloatRect boundaries)
{
    sf::Vector2f oldPosition = m_position;
    m_velocity += m_force/m_parameters->types[m_type].weight;
    m_force = sf::Vector2f(0.f, 0.f);
    m_position += m_velocity;
    while(m_position.x < boundaries.left)                    m_position.x += boundaries.width;
    while(m_position.x > boundaries.left + boundaries.width) m_position.x -= boundaries.width;
    while(m_position.y < boundaries.top)                     m_position.y += boundaries.height;
    while(m_position.y > boundaries.top + boundaries.height) m_position.y -= boundaries.height;
    
    for(auto &v: m_representation)
    {
	v.position += m_position - oldPosition;
    }
}

void Atom::draw(sf::RenderTarget& target)
{
    target.draw(&m_representation[0], m_representation.size(), sf::TriangleFan);
}
