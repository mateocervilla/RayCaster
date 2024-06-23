#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <memory>

class Wall : public sf::Drawable {
private:
    const sf::Vector2f m_point1;
    const sf::Vector2f m_point2;
    sf::RectangleShape line;

public:
    Wall(const sf::Vector2f point1, const sf::Vector2f point2);
    virtual ~Wall();

    void draw(sf::RenderTarget& window, sf::RenderStates states = sf::RenderStates::Default) const override;

    std::vector<sf::Vector2f> getPoints();
};