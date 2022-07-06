#pragma once
#include <EngineWindow.h>
#include <Entity.h>
#include <World.h>
#include <Random.h>

class Engine
{
protected:
	EngineWindow _window;	
	World _world;
	sf::Clock _deltaclock;
	float _deltaTime;

private:
	void Run();
		void GetInputs();
		void Update();
		void Render();
public:
	Engine();
	~Engine() = default;

	void GetSpawnRectangleInput(sf::Event& event, Vector mousePos);
	void GetSpawnTriangleInput(sf::Event& event, Vector mousePos);
	void GetSpawnCircleInput(sf::Event& event, Vector mousePos);
	void GetVelocitiesRandomizerInput(sf::Event& event);
	void GetClearInput(sf::Event& event);
};
