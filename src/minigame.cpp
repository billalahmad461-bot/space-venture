#include "../header/minigame.h"
#include "../header/pirate.h"
#include <algorithm>

Minigame::Minigame(Spaceship* ship, std::vector<Threat*> threats)
    : _ship(ship), _threats(threats) {
    sf::Texture tex;
    tex.loadFromFile("asset/sprites/space.png");
    _background.setTexture(tex);
}

Minigame::~Minigame() {
    for (auto t : _threats) delete t;
    for (auto b : _bullets) delete b;
}

bool Minigame::run(sf::RenderWindow& window) {
    sf::Clock clock;
    while (window.isOpen() && _ship->getShield()->getCurrentHp() > 0 && !_threats.empty()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
            handleInput(event);
        }
        update();
        window.clear();
        draw(window);
        window.display();
    }
    return _ship->getShield()->getCurrentHp() > 0;
}

void Minigame::update() {
    _ship->update();
    for (auto& b : _bullets) b->update();
    for (auto& t : _threats) {
        t->update();
        // Collision with ship
        if (t->getSprite().getGlobalBounds().intersects(_ship->getSpriteTop().getGlobalBounds())) {
            _ship->getShield()->takeDamage(t->getDmg());
            t->takeDamage(100);  // Destroy on collide
        }
        // Pirate attack
        if (dynamic_cast<Pirate*>(t)) t->attack();  // Add bullet if time
    }
    // Bullet collisions
    _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), [&](Bullet* b) {
        for (auto t : _threats) {
            if (b->getSprite().getGlobalBounds().intersects(t->getSprite().getGlobalBounds()) && b->isPlayer()) {
                t->takeDamage(b->getDmg());
                return true;
            }
        }
        // Enemy bullets on ship
        if (!b->isPlayer() && b->getSprite().getGlobalBounds().intersects(_ship->getSpriteTop().getGlobalBounds())) {
            _ship->getShield()->takeDamage(b->getDmg());
            return true;
        }
        return b->getPosition().y < 0 || b->getPosition().y > 600;
    }), _bullets.end());
    // Remove dead threats
    _threats.erase(std::remove_if(_threats.begin(), _threats.end(), [](Threat* t){ return t->getHp() <= 0; }), _threats.end());
}

void Minigame::draw(sf::RenderWindow& window) {
    window.draw(_background);
    window.draw(_ship->getSpriteTop());
    for (auto t : _threats) t->draw(window);
    for (auto b : _bullets) b->draw(window);
}

void Minigame::handleInput(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Space) _ship->shoot(_bullets);
    }
    // Movement
    _ship->setVelocity(sf::Vector2f(0,0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) _ship->setVelocity(sf::Vector2f(-5,0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) _ship->setVelocity(sf::Vector2f(5,0));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) _ship->setVelocity(sf::Vector2f(0,-5));
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) _ship->setVelocity(sf::Vector2f(0,5));
}
