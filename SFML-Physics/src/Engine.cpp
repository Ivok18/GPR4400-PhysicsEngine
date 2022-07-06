#include <Engine.h>

Engine::Engine()
{
    srand(time(NULL));

    // .. get engine window dimensions
    float windowWidth = _window.GetInstance().getSize().x;
    float windowHeight = _window.GetInstance().getSize().y;
    
    // .. set world grid width and height
    _world.GetGrid().SetDimensions(windowWidth, windowHeight);

	Run();
}

void Engine::Run()
{

    while (_window.GetInstance().isOpen())
    {
        GetInputs();
        Update();
        Render();
    }
}

void Engine::GetInputs()
{
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;

    while (_window.GetInstance().pollEvent(event))
    {
        // .. "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
        {
            _window.GetInstance().close();
        }
        if (event.type == sf::Event::KeyPressed) 
        {
            Vector mousePos;
            mousePos.SetX(sf::Mouse::getPosition(_window.GetInstance()).x);
            mousePos.SetY(sf::Mouse::getPosition(_window.GetInstance()).y);

            GetSpawnRectangleInput(event, mousePos);
            GetSpawnTriangleInput(event, mousePos);
            GetSpawnCircleInput(event, mousePos);
            GetVelocitiesRandomizerInput(event);
            GetClearInput(event);
        }
    }
}

void Engine::GetSpawnRectangleInput(sf::Event& event, Vector mousePos)
{
    if (event.key.code == sf::Keyboard::R)
    {
        _world.SpawnRectangle(Vector(50, 50), mousePos, Vector(0, 25), BodyType::DYNAMIC, sf::Color::Red);
    }
}

void Engine::GetSpawnCircleInput(sf::Event& event, Vector mousePos)
{
    if (event.key.code == sf::Keyboard::C)
    {
        _world.SpawnCircle(25, mousePos, Vector(0, 25), BodyType::DYNAMIC, sf::Color::Magenta);
    }
}

void Engine::GetSpawnTriangleInput(sf::Event& event, Vector mousePos)
{
    if (event.key.code == sf::Keyboard::T)
    {
        _world.SpawnTriangle(Vector(1.25f, 1.25f), mousePos, Vector(0, 25), BodyType::DYNAMIC, sf::Color::Cyan);
    }
}

void Engine::GetVelocitiesRandomizerInput(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Space)
    {
        for (auto& cell : _world.GetGrid().GetCells())
        {
            for (auto& entity : cell._entities)
            {
                Vector randomVelocity = Vector(Random::Randomize(-100,100), Random::Randomize(-800,800));
                entity->GetRigidbody().SetVelocity(randomVelocity);
            }
        }
    }
}

void Engine::GetClearInput(sf::Event& event)
{
    if (event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::RShift)
    {
        Grid& grid = _world.GetGrid();
        for (auto& cell : _world.GetGrid().GetCells())
        {
            for (auto& entity : cell._entities)
            {
                grid.RemoveEntityFromCell(entity);
            }
        }
    }
}

void Engine::Update()
{
    // ..clear window
    _window.GetInstance().clear(sf::Color::White);

    // ..update engine world
    _world.Update(_deltaTime);

    // ..get deltatime
    _deltaTime = _deltaclock.restart().asSeconds();
}

void Engine::Render()
{
    // .. render engine world
    _world.Render(_window.GetInstance());
}
