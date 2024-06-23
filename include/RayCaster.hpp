#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "Wall.hpp"
#include "Ray.hpp"

constexpr int WIDTH = 1800;
constexpr int HEIGHT = 800;

class RayCaster {
private:

    std::shared_ptr<sf::RenderWindow> m_window;
    sf::VideoMode m_videoMode;
    sf::Event m_ev;
    bool m_isWindowFocused;

    void initVariables();
    void initWindow();
    void initEnviroment();

    std::vector<Wall> m_walls;
    std::unique_ptr<Ray> m_ray;

    bool m_updateRay;

    sf::Clock m_clock;

public:
    RayCaster();
    virtual ~RayCaster();

    const bool running() const;

    void pollEvents();
    void update();
    void render();
};