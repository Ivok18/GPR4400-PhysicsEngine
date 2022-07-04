#pragma once
#include "SFML/Graphics.hpp"

class EngineWindow
{
protected:
	sf::RenderWindow _engineWindow;
	unsigned _widthOfGameWindow;
	unsigned _heighOfGameWindow;

public:
	EngineWindow();
	EngineWindow(unsigned width, unsigned height, std::string title);
	~EngineWindow() = default;

	sf::RenderWindow& GetInstance();
};