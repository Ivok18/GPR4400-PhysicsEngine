#include <World.h>

World::World()
{
	_gravity = 9.81f;
    _entities.reserve(10000000);
}

float World::GetGravity()
{
	return _gravity;
}

Grid& World::GetGrid()
{
	return _grid;
}

void World::SpawnRectangle(Vector size, Vector position, Vector velocity, BodyType bodyType, sf::Color color)
{
    sf::ConvexShape rectShape = ShapeBuilder::CreateRectShape(size, position, color);
    Entity rect = Entity(std::make_unique<sf::ConvexShape>(sf::ConvexShape(rectShape)));
    rect.GetRigidbody().SetBodyType(bodyType);
    _entities.emplace_back(rect);
    _entities.back().GetRigidbody().SetBodyType(bodyType);
    _grid.AddEntity(std::move(&_entities.back()));

    if (_entities.back().IsStuckInsideBorder(*this))  _grid.RemoveEntityFromCell(&_entities.back());
}

void World::SpawnTriangle(Vector size, Vector position, Vector velocity, BodyType bodyType, sf::Color color)
{
    sf::ConvexShape triangleShape = ShapeBuilder::CreateTriangleShape(size, position, color);
    Entity triangle = Entity(std::make_unique<sf::ConvexShape>(sf::ConvexShape(triangleShape)));
    triangle.GetRigidbody().SetBodyType(bodyType);
    _entities.emplace_back(triangle);
    _entities.back().GetRigidbody().SetBodyType(bodyType);
    _grid.AddEntity(std::move(&_entities.back()));

    if (_entities.back().IsStuckInsideBorder(*this))  _grid.RemoveEntityFromCell(&_entities.back());

}

void World::SpawnCircle(float radius, Vector position, Vector velocity, BodyType bodyType, sf::Color color)
{
    sf::CircleShape circleShape = ShapeBuilder::CreateCircleShape(radius, position, color);
    Entity circle = Entity(std::make_unique<sf::CircleShape>(sf::CircleShape(circleShape)));
    circle.GetRigidbody().SetBodyType(bodyType);
    _entities.emplace_back(circle);
    _entities.back().GetRigidbody().SetBodyType(bodyType);
    _grid.AddEntity(std::move(&_entities.back()));

    if (_entities.back().IsStuckInsideBorder(*this))  _grid.RemoveEntityFromCell(&_entities.back());
}

void World::Update(float dt)
{
    UpdateEntities(dt);
    ManageCollisions();
}

void World::UpdateEntities(float dt)
{
    for (auto& cell : _grid.GetCells())
    {
        for (auto& entity : cell._entities)
        {
            if (entity->GetRigidbody().GetBodyType() != BodyType::STATIC)
            {
                entity->Update(dt, *this);
            }
        }
    }
}

void World::ManageCollisions()
{
    Grid& grid = _grid;
    std::vector<Cell>& cells = grid.GetCells();

    for (int i = 0; i < grid.GetCells().size(); i++)
    {
        int x = i % grid.GetNumXCells();
        int y = i / grid.GetNumXCells();


        Cell& cell = cells[i];

        std::vector<Entity*>& entities = cell._entities;
        for (int j = 0; j < entities.size(); j++)
        {
            Entity* entity = entities[j];

            // .. handle collision with borders
            entity->HandleCollisionWithBorder(*this);

            // .. check collisions using space partitioning
                // .. manage collisions inside cell
            CheckCollision(entity, entities, j + 1);

            // .. manage collisions with neighbour cells
            if (x > 0)
            {
                CheckCollision(entity, grid.GetCell(x - 1, y)->_entities, 0);
                if (y > 0)
                {
                    CheckCollision(entity, grid.GetCell(x - 1, y - 1)->_entities, 0);
                }
                if (y < grid.GetNumYCells() - 1)
                {
                    CheckCollision(entity, grid.GetCell(x - 1, y + 1)->_entities, 0);
                }
            }
            if (y > 0)
            {
                CheckCollision(entity, grid.GetCell(x, y - 1)->_entities, 0);
            }

           
        }
    }
}

void World::CheckCollision(Entity* entity, std::vector<Entity*>& entitiesToCheck, int startingIndex)
{
    for (int i = startingIndex; i < entitiesToCheck.size(); i++)
    {
        Entity& other = *entitiesToCheck[i];
        {
            if (entity->IsCollidingWithEntity(other.GetCollider()))
            {
                if (MustClear(entity, &other))
                    _grid.RemoveEntityFromCell(entity);

                entity->ResolveCollision();
                other.ResolveCollision();
            }
        }
    }
}

bool World::MustClear(Entity* entity1, Entity* entity2)
{
    return std::abs(entity1->GetRigidbody().GetVelocity().GetY()) < 50 &&
        std::abs(entity2->GetRigidbody().GetVelocity().GetY()) < 50;       
}

void World::Render(sf::RenderWindow& window)
{
    for (auto& cell : _grid.GetCells())
    {
        for (auto& entity : cell._entities)
        {
            entity->Draw(window);
        }
    }
    window.display();
}