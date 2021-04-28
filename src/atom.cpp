#include "atom.hpp"


void AtomParameters::print()
{
    for(int i = 0; i < types.size(); ++i)
    {
	std::cout << "{\n";
	std::cout << "size=" << types[i].size << "\n";
	std::cout << "weight=" << types[i].weight << "\n";
	std::cout << "color=(" << ((int)types[i].color.r) << ", "
		  << ((int)types[i].color.g) << ", "
		  << ((int)types[i].color.b) << ")\n";
	std::cout << "relations={ ";
	for(int j = 0; j < types[i].relations.size(); ++j)
	{
	    std::cout << "{ " << types[i].relations[j].strength << " " << types[i].relations[j].maxDistance << " }";
	    if(j != types[i].relations.size()-1) std::cout << ", ";
	    else std::cout << " } \n";
	}
	std::cout << "}\n";
    }

    std::cout << "peakRelStr=" << peakRelStr << "\n";
    std::cout << "peakRepStr=" << peakRepStr << "\n";
    std::cout << "friction=" << friction << "\n";
    std::cout << "wrapping=" << wrapping << "\n";
}

std::vector< AtomType > generateAtomTypes
(int typeTotal, pairF sizeRange, pairF weightRange, pairF maxDistanceRange)
{
    std::vector< AtomType > result;
    std::vector< sf::Color > palette = generatePalette(typeTotal);

    for(int i=0; i < typeTotal; ++i)
    {
	float size = RandomF(sizeRange);
	std::vector< sf::Vector2f > circle = genCircleShape(size);
	
	result.push_back({size, RandomF(weightRange), palette[i], circle, {}});
	
	for(int j=0; j < typeTotal; ++j)
	{
	    result.back().relations.push_back({RandomF(-1.f, 1.f), RandomF(maxDistanceRange)});
	}
    }

    return result;
}

Atom::Atom(AtomParameters* parameters, int type, sf::Vector2f startPosition, sf::Vector2f startVelocity):
    m_parameters(parameters),
    m_type(type),
    m_position(startPosition),
    m_velocity(startVelocity),
    m_force(0.f, 0.f)
{
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

float Atom::calcRepelStr(float distance, float sumOfRadii)
{
    return m_parameters->peakRepStr;
    //return sqrt(1.f - distance/(sumOfRadii)) * m_parameters->peakRepStr;
    //return cos(distance * M_PI/2.f/size) * m_parameters->peakRepStr;
    //return 1.f/((distance - size)/size);
}

float Atom::calcRelStr(float distance, int targetType)
{
    float size = m_parameters->types[m_type].size;
    float maxDist = m_parameters->types[m_type].relations[targetType].maxDistance;

    return std::max(0.f,
		    m_parameters->peakRelStr * (1 + 2.f/(maxDist - size) *
						std::fabs(distance - (maxDist + size)/2.f)));
}

sf::Vector2f Atom::exertForce(int targetType, sf::Vector2f connector)
{
    sf::Vector2f result(0.f, 0.f);
    float distance = length(connector);
    
    if(distance <
       m_parameters->types[m_type].relations[targetType].maxDistance +
       m_parameters->types[m_type].size)
    {
	sf::Vector2f direction;
	float sumOfRadii = m_parameters->types[m_type].size + m_parameters->types[targetType].size;
	if(distance == 0.f) direction = Random2f(1.f, 1.f);
	else direction = connector/distance;
	
	// if the atoms are overlapping, they're always repelling
	
	if(distance < sumOfRadii)
	{
	    result = calcRepelStr(distance, sumOfRadii) * direction * -1.f;
	}
	else
	{
	    result = calcRelStr(distance, targetType) * direction
		* m_parameters->types[m_type].relations[targetType].strength;
	}
	if(isnan(result.x) || isnan(result.y))
	{
	    printVector(result);
	    std::cout << targetType << " " << distance << " ";
	    printVector(connector, true);
	}
    }
    
    return result;
}

void Atom::tick(sf::FloatRect boundaries)
{
    sf::Vector2f oldPosition = m_position;
    m_velocity -= m_velocity*m_parameters->friction;
    m_velocity += m_force/m_parameters->types[m_type].weight;
    m_force = sf::Vector2f(0.f, 0.f);
    m_position += m_velocity;

    if(m_parameters->wrapping)
    {
	while(m_position.x < boundaries.left)                    m_position.x += boundaries.width;
	while(m_position.x > boundaries.left + boundaries.width) m_position.x -= boundaries.width;
	while(m_position.y < boundaries.top)                     m_position.y += boundaries.height;
	while(m_position.y > boundaries.top + boundaries.height) m_position.y -= boundaries.height;
    }
    else
    {
	float size = m_parameters->types[m_type].size;
	if(m_position.x < boundaries.left + size)
	{
	    m_position.x = boundaries.left + size;
	    m_velocity.x = -m_velocity.x * m_parameters->bounce;
	}
	else if(m_position.x >= boundaries.left + boundaries.width - size)
	{
	    m_position.x = boundaries.left + boundaries.width - size;
	    m_velocity.x = -m_velocity.x * m_parameters->bounce;
	}
	
	if(m_position.y < boundaries.top + size)
	{
	    m_position.y = boundaries.top + size;
	    m_velocity.y = -m_velocity.y * m_parameters->bounce;
	}
	else if(m_position.y >= boundaries.top + boundaries.height - size)
	{
	    m_position.y = boundaries.top + boundaries.height - size;
	    m_velocity.y = -m_velocity.y * m_parameters->bounce;
	}
    }

    m_trail.push_back(m_representation);
    if(m_trail.size() > m_parameters->trailLength) m_trail.erase(m_trail.begin());
    for(int i = 0; i < m_trail.size(); ++i)
    {
	float transparency = ((float)i+1)/(m_parameters->trailLength+1) * 255.f * 0.1f;
	for(auto &v: m_trail[i])
	{
	    v.color.a = transparency;
	}
    }
    
    for(auto &v: m_representation)
    {
	v.position += m_position - oldPosition;
    }
}

void Atom::draw(sf::RenderTarget& target)
{
    target.draw(&m_representation[0], m_representation.size(), sf::TriangleFan);
    for(auto &t: m_trail)
    {
	target.draw(&t[0], t.size(), sf::TriangleFan);
    }
}
