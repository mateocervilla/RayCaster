#include "Ray.hpp"
#include <math.h>
#include <iostream>

#define RADIUS 10.f
#define RAYS 360

float calculateDistance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    float dx = point2.x - point1.x;
    float dy = point2.y - point1.y;
    return std::sqrt(dx * dx + dy * dy);
}

Ray::Ray(const sf::Vector2f pos, const std::vector<Wall>& walls)
: m_pos(pos), m_walls(walls)
{
    m_posDot.setOrigin(RADIUS/2,RADIUS/2);

    m_rays.resize(RAYS);
    double step = (2 * M_PI) / m_rays.size();
    double angle = 0;
    const sf::Vector2f initVect(0,10);

    for(int i = 0; i < m_rays.size(); i++) {
        m_rays[i].x = initVect.x * cos(angle) - initVect.y * sin(angle);
        m_rays[i].y = initVect.x * sin(angle) + initVect.y * cos(angle);
        angle += step;
    }

}

Ray::~Ray() {
}

void Ray::setPos(const sf::Vector2f point) {
    m_pos = point;
    m_posDot.setRadius(RADIUS);
    m_posDot.setPosition(m_pos);
    m_posDot.setFillColor(sf::Color::White);
    m_lines.clear();

    for(int i = 0; i < m_rays.size(); i++) {
        float dist = std::numeric_limits<float>::infinity();
        sf::Vector2f finalHitPoint;
        bool hit = false;
        for(int w = 0; w < m_walls.size(); w++) {
            sf::Vector2f hitPoint;
            if (hitWall(m_rays[i], m_walls[w], hitPoint)) {
                hit = true;
                float currDist = calculateDistance(m_pos, hitPoint);
                if(currDist < dist) {
                    dist = currDist;
                    finalHitPoint = hitPoint;
                }
            }
        }
        if(hit) {
            castRay(finalHitPoint);
        }
    }
}

bool Ray::hitWall(const sf::Vector2f dstPoint, Wall wall, sf::Vector2f& hitPoint) {
    const float x1 = wall.getPoints()[0].x;
    const float y1 = wall.getPoints()[0].y;
    const float x2 = wall.getPoints()[1].x;
    const float y2 = wall.getPoints()[1].y;
    const float x3 = m_pos.x;
    const float y3 = m_pos.y;
    const float x4 = dstPoint.x + m_pos.x;
    const float y4 = dstPoint.y + m_pos.y;

    const double den = (x1-x2)*(y3-y4)-(y1-y2)*(x3-x4);

    if(den == 0) {
        return false; // Parallel
    }

    const double t = ((x1-x3)*(y3-y4)-(y1-y3)*(x3-x4)) / den;
    const double u = -((x1-x2)*(y1-y3)-(y1-y2)*(x1-x3)) / den;

    if((t >= 0 && t <=1) && u >= 0){
        hitPoint.x = x1 + t * (x2 - x1);
        hitPoint.y = y1 + t * (y2 - y1);
        return true;
    }

    return false;
}

void Ray::castRay(const sf::Vector2f end) {
    const float lineLength = std::sqrt(std::pow(end.x - m_pos.x, 2) + std::pow(end.y - m_pos.y, 2));
    const float angle = std::atan2(end.y - m_pos.y, end.x - m_pos.x) * 180 / M_PI;    
    m_lines.push_back(sf::RectangleShape(sf::Vector2f(lineLength, 1.0f)));
    m_lines.back().setPosition(m_pos);
    // m_lines.back().setFillColor(sf::Color::White);
    m_lines.back().setFillColor(sf::Color(255,255,255,100));
    m_lines.back().setRotation(angle);
}

void Ray::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    for(int i = 0; i < m_lines.size(); i++) {
        window.draw(m_lines[i]);
    }
    window.draw(m_posDot);
}
