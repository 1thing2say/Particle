#include "Engine.h"
#include <iostream>

using namespace sf;
using namespace std;

Engine::Engine()
{
    // Create a window
    m_Window.create(VideoMode::getDesktopMode(), "Particle System", Style::Default);
    // Initialize sound
    if (!soundBuffer.loadFromFile("sound/bubble.ogg")) {
        cout << "Failed to load bubble.ogg" << endl;
        exit(1);
    }

    sound.setBuffer(soundBuffer);
    
    if (!wompBuffer.loadFromFile("sound/womp.ogg")) {
        cout << "Failed to load womp.ogg" << endl;
        exit(1);
    }

    womp.setBuffer(wompBuffer); 
}

void Engine::run()
{
    // Setup Clock
    Clock clock;
    
    // Run Unit Tests
    cout << "Starting Particle unit tests..." << endl;
    Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    p.unitTests();
    cout << "Unit tests complete.  Starting engine..." << endl;

    // Game Loop
    while (m_Window.isOpen())
    {
        // Restart returns the time elapsed since the last restart
        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}

void Engine::input()
{
    Event event;
    while (m_Window.pollEvent(event))
    {
        // Handle Escape or Close
        if (event.type == Event::Closed) {
            m_Window.close();
        }
        if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
            m_Window.close();
        }
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Right)
        {
            womp.play();
        }

        // Handle Mouse Click
        if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            // Play sound
            sound.play();
            // Create 5 particles
            for (int i = 0; i < 5; i++)
            {
                // Random vertices between 25 and 50
                int numPoints = (rand() % 26) + 25; 
                
                Vector2i mousePos = Mouse::getPosition(m_Window);
                
                // Construct particle and add to vector
                m_particles.emplace_back(m_Window, numPoints, mousePos);
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
    // Loop through particles
    for (auto it = m_particles.begin(); it != m_particles.end(); )
    {
        if (it->getTTL() > 0.0)
        {
            it->update(dtAsSeconds);
            ++it;
        }
        else
        {
            cout << "Particle expired! Erasing..." << endl;
            
            // erase returns the iterator to the next element
            it = m_particles.erase(it);
        }
    }
}

void Engine::draw()
{
    m_Window.clear();

    // Draw all particles
    for (const auto& particle : m_particles)
    {
        m_Window.draw(particle);
    }

    m_Window.display();
}