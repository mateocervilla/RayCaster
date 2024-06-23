#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <memory>

#include "Wall.hpp"

class Ray : public sf::Drawable {
private:
    sf::Vector2f m_pos;
    std::vector<sf::RectangleShape> m_lines;
    sf::CircleShape m_posDot;
    const std::vector<Wall> m_walls;
    void castRay(const sf::Vector2f end);
    bool hitWall(const sf::Vector2f dstPoint, Wall wall, sf::Vector2f& hitPoint);
    std::vector<sf::Vector2f> m_rays;

public:
    Ray(const sf::Vector2f pos, const std::vector<Wall>& walls);
    virtual ~Ray();

    void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override;

    void setPos(const sf::Vector2f point);;
};