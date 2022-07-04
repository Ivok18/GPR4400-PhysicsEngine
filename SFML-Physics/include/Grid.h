#pragma once
#include <cmath>
#include <Entity.h>
#include <vector>

struct Cell
{
	std::vector<Entity*> _entities;
};

class Grid
{
private:
	std::vector<Cell> _cells;
	int _cellSize;
	int _width;
	int _height;
	int _numXCells;
	int _numYCells;

public:
	Grid();
	Grid(int width, int height, int cellSize);
	~Grid();

	void AddEntity(Entity* entityP);
	void AddEntity(Entity* entityP, Cell* cellP);
	Cell* GetCell(int gridX, int gridY);
	Cell* GetCell(Vector windowCoord);
	std::vector<Cell>& GetCells();
	void RemoveEntityFromCell(Entity* entityP);
	float GetWidth();
	float GetHeight();
	int GetNumXCells();
	int GetNumYCells();
	void SetDimensions(float width, float height);
	void UpdateCellCount();

};