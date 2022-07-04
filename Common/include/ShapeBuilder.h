#pragma once
#include <SFML/Graphics.hpp>
#include "Vector.h"
static class ShapeBuilder
{
public:
    static sf::ConvexShape CreateRectShape(Vector size, Vector position, sf::Color color);
    static sf::CircleShape CreateCircleShape(float radius, Vector position, sf::Color color);
    static sf::ConvexShape CreateTriangleShape(Vector size, Vector position, sf::Color color);
};
