#include "../header/minigame.h"
#include <algorithm>

Minigame::Minigame(Spaceship* ship, std::vector<Threat*> threats)
    : _ship(ship), _threats(threats), _done(false), _survived(false) {
    sf::Texture tex;
    tex.loadFromFile("asset/sprites/space.png");
    _background.setTexture(tex);
    _ship->setPosition(sf::Vector2f(400, 500));
    _ship->setVelocity(sf::Vector2f(0, 0));
}

Minigame::~Minigame() {
    for (auto t : _threats) delete t;
    for (auto b : _bullets) delete b;
}

void Minigame::update(float delta) {
    _ship->update(delta);
    for (auto b : _bullets) b->update(delta);
    for (auto t : _threats) {
        t->update(delta);
        t->attack(_bullets, _ship->getPosition());
        if (t->getSprite().getGlobalBounds().intersects(_ship->getSpriteTop().getGlobalBounds())) {
            _ship->getShield()->takeDamage(t->getDmg());
            t->takeDamage(100);
        }
        // Remove off-screen threats
        if (t->getPosition().y > 600) {
            delete t;
            t = nullptr;
        }
    }
    _threats.erase(std::remove_if(_threats.begin(), _threats.end(), [](Threat* t){ return t == nullptr || t->getHp() <= 0; }), _threats.end());
    _bullets.erase(std::remove_if(_bullets.begin(), _bullets.end(), [&](Bullet* b) {
        for (auto it = _threats.begin(); it != _threats.end(); ++it) {
            if (b->getSprite().getGlobalBounds().intersects((*it)->getSprite().getGlobalBounds()) && b->isPlayer()) {
                (*it)->takeDamage(b->getDmg());
                return true;
            }
        }
        if (!b->isPlayer() && b->getSprite().getGlobalBounds().intersects(_ship->getSpriteTop().getGlobalBounds())) {
            _ship->getShield()->takeDamage(b->getDmg());
            return true;
        }
        return b->getPosition().y < 0 || b->getPosition().y > 600;
    }), _bullets.end());
    if (_ship->getShield()->getCurrentHp() <= 0 || _threats.empty()) {
        _done = true;
        _survived = _ship->getShield()->getCurrentHp() > 0;
    }
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
    sf::Vector2f vel(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) vel.x -= 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) vel.x += 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) vel.y -= 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) vel.y += 200.f;
    _ship->setVelocity(vel);
}

bool Minigame::isDone() const { return _done; }

bool Minigame::survived() const { return _survived; }

void Minigame::reset() {
    _done = false;
    _survived = false;
    // Reinit threats if needed
}
