#include "RayCaster.hpp"
#include <math.h>
#include <iostream>
#include <random>

#define CONTOURS 0

RayCaster::RayCaster() {
    initVariables();
    initWindow();
    initEnviroment();
}

RayCaster::~RayCaster() {
}

void RayCaster::initVariables() {
    m_window = nullptr;
    m_isWindowFocused = true;
    m_updateRay = true;
}

void RayCaster::initWindow() {
    m_videoMode.height = HEIGHT;
    m_videoMode.width = WIDTH;
    
    m_window = std::make_shared<sf::RenderWindow>(m_videoMode, "RayCaster", sf::Style::Close);
    m_window->setFramerateLimit(75);
}

void RayCaster::initEnviroment() {
    // Initialize random number generators
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> disX(0, WIDTH);
    std::uniform_real_distribution<float> disY(0, HEIGHT);

    // Generate random walls
    for(int i = 0; i < 8; i++) {
        m_walls.push_back(Wall(sf::Vector2f(disX(gen),disY(gen)), sf::Vector2f(disX(gen),disY(gen))));
    }

#if CONTOURS
    m_walls.push_back(Wall(sf::Vector2f(0,0), sf::Vector2f(WIDTH,0)));
    m_walls.push_back(Wall(sf::Vector2f(WIDTH,0), sf::Vector2f(WIDTH,HEIGHT)));
    m_walls.push_back(Wall(sf::Vector2f(0,HEIGHT), sf::Vector2f(WIDTH,HEIGHT)));
    m_walls.push_back(Wall(sf::Vector2f(0,0), sf::Vector2f(0,HEIGHT)));
#endif

    m_ray = std::make_unique<Ray>(sf::Vector2f(500,500), m_walls);
    m_ray->setPos(sf::Vector2f(600,480));
}

void RayCaster::update() {
    pollEvents();
}

void RayCaster::render() {

    /*
        - clear old frame
        - render objects
        - display frame in window

        Renders objects
    */

    m_window->clear(sf::Color::Black);

    for(int w = 0; w < m_walls.size(); w++) {
        m_walls[w].draw(*m_window);
    }
    m_ray->draw(*m_window);

    m_window->display();
}

void RayCaster::pollEvents() {
    while (m_window->pollEvent(m_ev)) {
        switch (m_ev.type) {
            case sf::Event::Closed:
                m_window->close();
                break;
            // Window focus events
            case sf::Event::GainedFocus:
                m_isWindowFocused = true;
                break;
            case sf::Event::LostFocus:
                m_isWindowFocused = false;
                break;

            case sf::Event::MouseMoved:
                if(m_updateRay && m_isWindowFocused) {
                    sf::Vector2i position = sf::Mouse::getPosition(*m_window);
                    m_ray->setPos(sf::Vector2f(position));
                    m_updateRay = false;
                }
                else {
                     m_updateRay = true;
                }
                break;

        }
    }
}

const bool RayCaster::running() const {
    return m_window->isOpen();
}
