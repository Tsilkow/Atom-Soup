#include "soup.hpp"


Soup::Soup(AtomParameters* AParams, sf::RenderWindow* window, int atomTotal, sf::FloatRect boundaries):
    m_AParams(AParams),
    m_window(window),
    m_boundaries(boundaries)
{
    for(int i = 0; i < atomTotal; ++i)
    {
	m_atoms.emplace_back(m_AParams,
			     RandomI(0, m_AParams->types.size()-1),
			     Random2f(m_boundaries),
			     //sf::Vector2f(0.f, 0.f));
			     makeVector(RandomF(0.f, 10.f), RandomF(0, 2*M_PI)));
    }
}

bool Soup::simulate()
{
    while(m_atoms.size() > 0)
    {
	sf::Event event;

	while(m_window->pollEvent(event))
	{
	    switch(event.type)
	    {
		case sf::Event::Closed:
		    return false;
		    break;
		case sf::Event::KeyPressed:
		    if(m_window->hasFocus())
		    {
			switch(event.key.code)
			{
			    case sf::Keyboard::Escape:
				return false;
				break;
			}
		    }
	    }
	}

	for(auto &a: m_atoms)
	{
	    for(auto &b: m_atoms)
	    {
		if(&a != &b)
		{
		    b.addForce(
			   a.exertForce(b.getType(),
					connector(a.getPosition(), b.getPosition(), m_boundaries,
						  m_AParams->wrapping)));
		}
	    }
	}

	for(int i=0; i < m_atoms.size(); ++i)//for(auto &a: m_atoms)
	{
	    m_atoms[i].tick(m_boundaries);
	}

	draw();
	m_window->display();
    }

    return false;
}

void Soup::draw()
{
    m_window->clear();
    for(auto &a: m_atoms)
    {
	a.draw(*m_window);
    }
}
