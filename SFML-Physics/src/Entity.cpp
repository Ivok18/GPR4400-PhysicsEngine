#include <Entity.h>
#include <World.h>

Entity::Entity()
{
    Id++;
    _id = Id;
    _shape = nullptr;
    _ownerCell = nullptr;
    _ownerCellVectorIndex = -1;
}

Entity::Entity(std::unique_ptr<sf::Shape> shape)
{
    Id++;
    _id = Id;
    _shape = std::move(shape);
    _ownerCell = nullptr;
    _ownerCellVectorIndex = -1;
    
}

Entity::Entity(Entity& const entity)
{
    _shape = std::move(entity._shape);
}

bool Entity::operator!=(Entity& other)
{
    return (_id != other._id);
}

int Entity::GetID()
{
    return _id;
}

void Entity::SetPosition(Vector pos)
{
    _shape->setPosition(pos.GetX(), pos.GetY());
}

Vector Entity::GetPosition()
{
    return Vector(GetCollider().left + GetCollider().width / 2, GetCollider().top + GetCollider().height / 2);  
}

void Entity::Move(Vector offset)
{
    _shape->move(offset.GetX(), offset.GetY());
}

std::unique_ptr<sf::Shape>& Entity::GetShape()
{
    return _shape;
}

sf::FloatRect Entity::GetCollider()
{
    return _shape->getGlobalBounds();
}

bool Entity::IsCollidingWithEntity(sf::FloatRect& otherCollider)
{
    return (GetCollider().left <= otherCollider.left + otherCollider.width &&
        GetCollider().left + otherCollider.width >= otherCollider.left &&
        GetCollider().top <= otherCollider.top + otherCollider.height &&
        GetCollider().top + otherCollider.height >= otherCollider.top);
}

Rigidbody& Entity::GetRigidbody()
{
    return _rigidbody;
}

Cell* Entity::GetOwnerCell()
{
    return _ownerCell;
}

void Entity::SetOwnerCell(Cell* owner)
{
    _ownerCell = owner;
}

int Entity::GetOwnerCellVectorIndex()
{
    return _ownerCellVectorIndex;
}

void Entity::SetOwnerCellVectorIndex(int newIndex)
{
    _ownerCellVectorIndex = newIndex;
}

bool Entity::IsStuckInsideBorder(World& world)
{
    Grid& grid = world.GetGrid();

    return  GetPosition().GetY() + GetCollider().height / 2 >= grid.GetHeight()
        || GetPosition().GetY() - GetCollider().height / 2 <= 0
        || GetPosition().GetX() + GetCollider().width / 2 >= grid.GetWidth()
        || GetPosition().GetX() - GetCollider().width / 2 <= 0
        && std::abs(_rigidbody.GetVelocity().GetY()) < 50;
}

void Entity::HandleCollisionWithBorder(World& world)
{
    if (GetPosition().GetY() + GetCollider().height / 2 >= world.GetGrid().GetHeight())
    {
        ResolveCollision();
    }
    if (GetPosition().GetY() - GetCollider().height / 2 <= 0)
    {
        ResolveCollision();
    }
    if (GetPosition().GetX() + GetCollider().width / 2 >= world.GetGrid().GetWidth())
    {
        ResolveCollision();
    }
    if (GetPosition().GetX() - GetCollider().width / 2 <= 0)
    {
        ResolveCollision();
    }

}

void Entity::ResolveCollision()
{
     Vector newVel = _rigidbody.GetVelocity() * -1;
     _rigidbody.SetVelocity(Vector(newVel.GetX(), newVel.GetY() / 1.15f)); 
}

void Entity::Draw(sf::RenderWindow& window)
{
    window.draw(*_shape);
}

void Entity::Update(float dt, World& world)
{    
    // .. apply gravity
    _rigidbody.GetVelocity().SetY(_rigidbody.GetVelocity().GetY() + (_rigidbody.GetMass() * world.GetGravity() / 64));

    // .. move entity according to it's velocity
    Move(Vector(_rigidbody.GetVelocity().GetX() * dt, _rigidbody.GetVelocity().GetY() * dt));
    
    // .. check to see if the entity has changed cell in the grid
    Cell* newCell = world.GetGrid().GetCell(GetPosition());
    if (newCell != _ownerCell)
    {
        world.GetGrid().RemoveEntityFromCell(this);
        world.GetGrid().AddEntity(this, newCell);
    }

}

int Entity::Id = 0;