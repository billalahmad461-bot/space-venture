#include "../header/game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

Game::Game() : _window(sf::VideoMode(800, 600), "Space Venture"), _state(GameState::PLANET) {
    srand(static_cast<unsigned int>(time(NULL)));
    _font.loadFromFile("asset/fonts/font.ttf");  // Assume font added
    _message.setFont(_font);
    init();
}

void Game::init() {
    _starting_region = new Region("Starting Region", false, 1);
    setupRegion();
    _ship = new Spaceship("Player Ship");
    _ship->setRegion(_starting_region);
    _ship->setCurrentPlanet(_starting_region->getPlanets()[0]);
    updatePlanetScreen();
}

void Game::setupRegion() {
    Planet* start = new Planet("Start", _starting_region);
    start->loadSprite("asset/sprites/space.png");
    Planet* kepler_a = new Planet("Kepler A", _starting_region);
    kepler_a->loadSprite("asset/sprites/kepler-a.png");
    kepler_a->addResource(new Resource("Elixir", false, 50, 0));
    Planet* kepler_b = new Planet("Kepler B", _starting_region);
    kepler_b->loadSprite("asset/sprites/kepler-b.png");
    kepler_b->addResource(new Resource("Mithrol", false, 100, 0));
    _starting_region->addPlanet(start);
    _starting_region->addPlanet(kepler_a);
    _starting_region->addPlanet(kepler_b);
}

void Game::run() {
    while (_window.isOpen()) {
        sf::Event event;
        while (_window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) _window.close();
            if (event.type == sf::Event::MouseButtonPressed && _state == GameState::PLANET) {
                sf::Vector2f mouse = _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
                for (auto& btn : _buttons) btn.handleClick(mouse);
            }
        }
        _window.clear();
        _window.draw(_background);
        for (auto& btn : _buttons) btn.draw(_window);
        _window.draw(_message);
        _window.display();
    }
}

void Game::updatePlanetScreen() {
    _background = _ship->getCurrentPlanet()->getSprite();
    _message.setString("You are on " + _ship->getCurrentPlanet()->getName());
    _buttons.clear();
    addButton(sf::Vector2f(100,100), "Travel", [this](){
        // Choose planet, assume to next
        Planet* next = _starting_region->getPlanets()[1];  // Simple
        _ship->travel(_starting_region, next);
        updatePlanetScreen();
    });
    addButton(sf::Vector2f(100,150), "Collect Resources", [this](){
        _ship->collectResources("Elixir", _ship->countMiners());  // Assume
    });
    // Add other buttons for refuel, repair, etc.
}

void Game::addButton(sf::Vector2f pos, std::string label, std::function<void()> on_click) {
    _buttons.emplace_back(pos, sf::Vector2f(200,50), label, _font, on_click);
}
