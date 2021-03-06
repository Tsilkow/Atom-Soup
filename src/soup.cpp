#include "soup.hpp"


Soup::Soup(AtomParameters* AParams, sf::RenderWindow* window, sf::Font* font, int atomTotal, sf::FloatRect boundaries):
    m_AParams(AParams),
    m_window(window),
    m_boundaries(boundaries),
    m_scrollSpeed(5.f),
    m_zoomSpeed(0.01f)
{
    for(int i = 0; i < atomTotal; ++i)
    {
	m_atoms.emplace_back(m_AParams,
			     RandomI(0, m_AParams->types.size()-1),
			     Random2f(m_boundaries),
			     //sf::Vector2f(0.f, 0.f));
			     makeVector(RandomF(0.f, 10.f), RandomF(0, 2*M_PI)));
    }
    
    m_mainView.setCenter(sf::Vector2f(0.f, 0.f));
    m_mainView.setSize(sf::Vector2f(m_boundaries.width, m_boundaries.height));
    m_mainView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));
    m_window->setView(m_mainView);
    m_textView.setCenter(sf::Vector2f(0.f, 0.f));
    m_textView.setSize(sf::Vector2f(m_boundaries.width, m_boundaries.height));
    m_textView.setViewport(sf::FloatRect(0.f, 0.f, 1.f, 1.f));

    m_boundRepres.emplace_back(sf::Vector2f(m_boundaries.left,
					    m_boundaries.top),
			       sf::Color::White);
    m_boundRepres.emplace_back(sf::Vector2f(m_boundaries.left + m_boundaries.width,
					    m_boundaries.top),
			       sf::Color::White);
    m_boundRepres.emplace_back(sf::Vector2f(m_boundaries.left + m_boundaries.width,
					    m_boundaries.top + m_boundaries.height),
			       sf::Color::White);
    m_boundRepres.emplace_back(sf::Vector2f(m_boundaries.left,
					    m_boundaries.top + m_boundaries.height),
			       sf::Color::White);
    m_boundRepres.emplace_back(sf::Vector2f(m_boundaries.left,
					    m_boundaries.top),
			       sf::Color::White);

    m_fpsCounter.setFont(*font);
    m_fpsCounter.setCharacterSize(16);
    m_fpsCounter.setPosition(m_boundaries.left, m_boundaries.top);
    m_fpsCounter.setFillColor(sf::Color::White);
}

bool Soup::simulate(bool record)
{
    m_ticks = 0;
    sf::Clock clock;
    
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

	if(m_window->hasFocus())
	{   
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up   ))
		m_mainView.move(m_scrollSpeed * sf::Vector2f( 0.f, -1.f));
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down ))
		m_mainView.move(m_scrollSpeed * sf::Vector2f( 0.f,  1.f));
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_mainView.move(m_scrollSpeed * sf::Vector2f( 1.f,  0.f));
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left ))
		m_mainView.move(m_scrollSpeed * sf::Vector2f(-1.f,  0.f));
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Add))
		m_mainView.zoom(1.f - m_zoomSpeed);
	    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Subtract))
		m_mainView.zoom(1.f + m_zoomSpeed);
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

	if(modulo(m_ticks, 60) == 0)
	{
	    float currTime = clock.restart().asSeconds();
	    float fps = 60.f / (currTime);

	    m_fpsCounter.setString(strPrecRound(fps, 0));
	}
	
	draw(record);
	m_window->display();
	++m_ticks;
    }

    return false;
}

void Soup::capture()
{
    sf::Texture result;
    result.create(m_window->getSize().x, m_window->getSize().y);
    result.update(*m_window);
    result.copyToImage().saveToFile("captured/" + std::to_string(m_ticks) + ".png");
}

void Soup::draw(bool record)
{
    m_window->clear();
    m_window->setView(m_mainView);
    for(auto &a: m_atoms)
    {
	a.draw(*m_window);
    }
    if(!record) m_window->draw(&m_boundRepres[0], m_boundRepres.size(), sf::LineStrip);
    if(record)  capture();
    m_window->setView(m_textView);
    m_window->draw(m_fpsCounter);
}
