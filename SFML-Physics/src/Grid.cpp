#include <Grid.h>

Grid::Grid()
{
	_width = 1000;
	_height = 1000;
	_cellSize = 200;
	_numXCells = std::ceil((float)_width / _cellSize);
	_numYCells = std::ceil((float)_height / _cellSize);

	_cells.resize(_numYCells * _numXCells);
}

Grid::Grid(int width, int height, int cellSize)
{
	_width = width;
	_height = height;
	_cellSize = cellSize;
	_numXCells = std::ceil((float)_width / _cellSize);
	_numYCells = std::ceil((float)_height / _cellSize);

	_cells.resize(_numYCells * _numXCells);
}

Grid::~Grid()
{

}

// .. add entity in grid
void Grid::AddEntity(Entity* entityP)
{
	Cell* entityCell = GetCell(entityP->GetPosition());
	entityCell->_entities.push_back(entityP);
	entityP->SetOwnerCell(entityCell);
	entityP->SetOwnerCellVectorIndex(entityCell->_entities.size() - 1);
}


// .. add entity in grid in the specified cell
void Grid::AddEntity(Entity* entityP, Cell* cellP)
{
	cellP->_entities.push_back(entityP);
	entityP->SetOwnerCell(cellP);
	entityP->SetOwnerCellVectorIndex(cellP->_entities.size() - 1);
}

// .. get cell based on grid coordinates
Cell* Grid::GetCell(int gridX, int gridY)
{
	if (gridX < 0) gridX = 0;
	if (gridX >= _numXCells) gridX = _numXCells;
	if (gridY < 0) gridY = 0;
	if (gridY >= _numYCells) gridY = _numYCells;

	int cellIndex = gridY * _numXCells + gridX;
	return &_cells[cellIndex];
}

// .. get cell based on window coordinates
Cell* Grid::GetCell(Vector windowCoord)
{
	int cellX = (int)windowCoord.GetX() / _cellSize;
	int cellY = (int)windowCoord.GetY() / _cellSize;

	return GetCell(cellX, cellY);
}

std::vector<Cell>& Grid::GetCells()
{
	return _cells;
}

void Grid::RemoveEntityFromCell(Entity* entityP)
{
	std::vector<Entity*>& entities = entityP->GetOwnerCell()->_entities;
	entities[entityP->GetOwnerCellVectorIndex()] = entities.back();
	entities.pop_back();
	if (entityP->GetOwnerCellVectorIndex() < entities.size())
	{
		entities[entityP->GetOwnerCellVectorIndex()]->SetOwnerCellVectorIndex(entityP->GetOwnerCellVectorIndex());
	}
	entityP->SetOwnerCellVectorIndex(-1);
	entityP->SetOwnerCell(nullptr);
}


float Grid::GetWidth()
{
	return _width;
}

float Grid::GetHeight()
{
	return _height;
}

int Grid::GetNumXCells()
{
	return _numXCells;
}

int Grid::GetNumYCells()
{
	return _numYCells;
}

// .. set grid dimensions in pixels
void Grid::SetDimensions(float width, float height)
{
	_width = width;
	_height = height;

	UpdateCellCount();
}

void Grid::UpdateCellCount()
{
	_numXCells = std::ceil((float)_width / _cellSize);
	_numYCells = std::ceil((float)_height / _cellSize);

	_cells.resize(_numYCells * _numXCells);
}





