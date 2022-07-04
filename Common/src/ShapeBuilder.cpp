#include "ShapeBuilder.h"

sf::ConvexShape ShapeBuilder::CreateRectShape(Vector size, Vector position, sf::Color color)
{
    sf::ConvexShape box;
    box.setPointCount(4);
    box.setPoint(0, sf::Vector2f(0, 0));
    box.setPoint(1, sf::Vector2f(0, size.GetY()));
    box.setPoint(2, sf::Vector2f(size.GetX(), size.GetY()));
    box.setPoint(3, sf::Vector2f(size.GetX(), 0));
    box.setOrigin(size.GetX() / 2, size.GetY() / 2);
    box.setPosition(position.GetX(), position.GetY());
    box.setFillColor(color);
    return box;
}

sf::CircleShape ShapeBuilder::CreateCircleShape(float radius, Vector position, sf::Color color)
{
    sf::CircleShape circle;
    circle.setRadius(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(position.GetX(), position.GetY());
    circle.setFillColor(color);
    return circle;
}

sf::ConvexShape ShapeBuilder::CreateTriangleShape(Vector scale, Vector position, sf::Color color)
{
    sf::ConvexShape triangle;
    triangle.setPointCount(3);
    triangle.setPoint(0, sf::Vector2f(0, 0));
    triangle.setPoint(1, sf::Vector2f(-20, 36));
    triangle.setPoint(2, sf::Vector2f(20, 36));
    triangle.setScale(scale.GetX(), scale.GetY());
    triangle.setOrigin(20, 18);
    triangle.setPosition(position.GetX(), position.GetY());
    triangle.setFillColor(color);
    return triangle;
}