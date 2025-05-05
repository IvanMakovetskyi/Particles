#include "Engine.h"

Engine::Engine()
{
    // Initialize the window
    VideoMode vm = VideoMode::getDesktopMode();
    m_Window.create(vm);
}

void Engine::run()
{
    // Construct a clock
    Clock clock;

    // Local Particle for testing
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    // Game loop
    while (m_Window.isOpen())
    {
        // Restarts the clock
        // Sets the time to seconds
        Time dt clock.restart();
        dtAsSeconds = dt.asSeconds;

        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input()
{
    // Handling the events:
    Event event;
    while (m_Window.pollEvent(event))
    {
        // Request for closing the window
        if (event.type == Event::Closed)
        {
            window.close();
        }
    
        // The escape key was pressed
        if ((event.type == Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
        {
            window.close();
        }

        // Mouse click
        if (event.type == Event::MouseButtonPressed)
        {
            // Check is it left button
            if (event.mouseButton.button == Mouse::Left)
            {
                // Loop to costruct 5 particles
                for (size_t i; i < 5; i++)
                {
                    // rand number in range [25:50]
                    // use that for number of vertices
                    int numPoints = (rand () % 26) + 25;

                    // Vector for click coordinates
                    Vector2i mouseClickPosition = {event.mouseButton.x, event.mouseButton.y};
                    
                    // Add the Particle to a vector
                    m_particles.push_back(Particle(m_Window, numPoints, mouseClickPosition));
                }
            }
        }
    }
}


void Engine::update(float dtAsSeconds)
{
    size t i;
    // Go through each Particle
    for (i < m_particles.size())
    {
        particle = m_particles.at(i);
        // If the TTL is not passed
        // update
        if (particle.getTTL > 0.0)
        {
            particle.update(dtAsSeconds);
            i++;
        }
        // or delete if passed
        else
        {
            i = m_particles.erase(i);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();

    // Go through each Particle and call draw function
    for (size_t i; i < m_particles.size(); i++)
    {
        m_Window.draw(m_particles.at(i));
    }

    m_Window.display();
}