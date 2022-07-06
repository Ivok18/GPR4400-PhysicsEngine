#pragma once
#include <Vector.h>
#include <SFML/Graphics.hpp>
#include <Rigidbody.h>


struct Cell;
class World;


class Entity
{
protected:
    static int Id;
    int _id = 0;
    std::unique_ptr<sf::Shape> _shape;
    sf::FloatRect _collider;
    Rigidbody _rigidbody;
    Cell* _ownerCell;
    int _ownerCellVectorIndex;


public:
    Entity();
    Entity(std::unique_ptr<sf::Shape> shape);
    Entity(Entity& entity);
    ~Entity() = default;
    bool operator != (Entity& other);
   
    int GetID();

    void SetPosition(Vector pos);
    Vector GetPosition();
    void Move(Vector offset);

    std::unique_ptr<sf::Shape>& GetShape();

    sf::FloatRect GetCollider();
    bool IsCollidingWithEntity(sf::FloatRect& otherCollider);

    Rigidbody& GetRigidbody();

    Cell* GetOwnerCell();
    void SetOwnerCell(Cell* owner);
    int GetOwnerCellVectorIndex();
    void SetOwnerCellVectorIndex(int newIndex);

    bool IsStuckInsideBorder(World& world);
    void HandleCollisionWithBorder(World& world);
    void ResolveCollision();

    void Update(float dt, World& world);
    void Draw(sf::RenderWindow& window);


};