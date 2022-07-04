#include "EngineWindow.h"


EngineWindow::EngineWindow() : _widthOfGameWindow(1200), _heighOfGameWindow(800)
{
	_engineWindow.create(sf::VideoMode(_widthOfGameWindow, _heighOfGameWindow), "Physics Engine");
}

EngineWindow::EngineWindow(unsigned width, unsigned height, std::string title) : _widthOfGameWindow(width), _heighOfGameWindow(height)
{
	_engineWindow.create(sf::VideoMode(_widthOfGameWindow, _heighOfGameWindow), title);
}

sf::RenderWindow& EngineWindow::GetInstance()
{
	return _engineWindow;
}