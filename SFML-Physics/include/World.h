#pragma once
#include <vector>
#include <Entity.h>
#include <Grid.h>
#include <ShapeBuilder.h>

class World
{
private:
	Grid _grid;
	float _gravity;
	std::vector<Entity> _entities;
		
public:
	World();
	~World() = default;

	float GetGravity();
	Grid& GetGrid();

	void SpawnRectangle(Vector size, Vector position, Vector velocity, BodyType bodyType, sf::Color color);
	void SpawnTriangle(Vector scale, Vector position, Vector velocity, BodyType bodyType, sf::Color color);
	void SpawnCircle(float radius, Vector position, Vector velocity, BodyType bodyType, sf::Color color);

	void Update(float dt);
	void UpdateEntities(float dt);
	void ManageCollisions();
	void CheckCollision(Entity* entity, std::vector<Entity*>& entities, int startingIndex);
	bool MustClear(Entity* entity1, Entity* entity2);

	void Render(sf::RenderWindow& window);
};