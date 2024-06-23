#include "Wall.hpp"
#include <math.h>
#include <iostream>


Wall::Wall(const sf::Vector2f point1, const sf::Vector2f point2)
: m_point1(point1), m_point2(point2)
{
    float lineLength = std::sqrt(std::pow(point2.x - point1.x, 2) + std::pow(point2.y - point1.y, 2));
    float angle = std::atan2(point2.y - point1.y, point2.x - point1.x) * 180 / M_PI;
    line = sf::RectangleShape(sf::Vector2f(lineLength, 5.0f)); // 5.0f is the thickness of the line
    line.setPosition(point1);
    line.setFillColor(sf::Color::White);
    line.setRotation(angle);
}

Wall::~Wall() {
}

void Wall::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    window.draw(line);
}

std::vector<sf::Vector2f> Wall::getPoints() {
    return {m_point1, m_point2};
}
