#include "../header/minigame.h"
#include <algorithm>

Minigame::Minigame(Spaceship* ship, std::vector<Threat*> threats) : _ship(ship), _threats(threats), _done(false), _survived(false) {
    _background_texture.loadFromFile("asset/sprites/backgrounds/space.png");
    _background.setTexture(_background_texture);
    _ship->setPosition(sf::Vector2f(400, 500));
    _ship->setVelocity(sf::Vector2f(0, 0));
}

Minigame::~Minigame() {
    for (auto t : _threats) delete t;
    for (auto b : _bullets) delete b;
}

void Minigame::update(float delta) {
    sf::Vector2f vel(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) vel.x -= 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) vel.x += 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) vel.y -= 200.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) vel.y += 200.f;
    _ship->setVelocity(vel);

    _ship->update(delta);

    // Update all threats and handle direct collisions with ship
    for (Threat* t : _threats) {
        t->update(delta);
        t->attack(_bullets, _ship->getPosition());
        if (t->getSprite().getGlobalBounds().intersects(_ship->getSpriteTop().getGlobalBounds())) {
            _ship->getShield()->takeDamage(t->getDmg());
            t->takeDamage(100);
        }
    }

    // Update all bullets
    for (Bullet* b : _bullets) {
        b->update(delta);
    }

    // Collect bullets to remove
    std::vector<Bullet*> bullets_to_remove;
    for (Bullet* b : _bullets) {
        if (b->getPosition().y < 0 || b->getPosition().y > 600) {
            bullets_to_remove.push_back(b);
            continue;
        }

        bool removed = false;
        if (b->isPlayer()) {
            for (Threat* t : _threats) {
                if (b->getSprite().getGlobalBounds().intersects(t->getSprite().getGlobalBounds())) {
                    t->takeDamage(b->getDmg());
                    bullets_to_remove.push_back(b);
                    removed = true;
                    break;
                }
            }
        } else {
            if (b->getSprite().getGlobalBounds().intersects(_ship->getSpriteTop().getGlobalBounds())) {
                _ship->getShield()->takeDamage(b->getDmg());
                bullets_to_remove.push_back(b);
                removed = true;
            }
        }
        if (removed) continue;
    }

    // Collect threats to remove
    std::vector<Threat*> threats_to_remove;
    for (Threat* t : _threats) {
        if (t->getPosition().y > 600 || t->getHp() <= 0) {
            threats_to_remove.push_back(t);
        }
    }

    // Remove and delete bullets
    for (Bullet* b : bullets_to_remove) {
        auto it = std::find(_bullets.begin(), _bullets.end(), b);
        if (it != _bullets.end()) {
            _bullets.erase(it);
        }
        delete b;
    }

    // Remove and delete threats
    for (Threat* t : threats_to_remove) {
        auto it = std::find(_threats.begin(), _threats.end(), t);
        if (it != _threats.end()) {
            _threats.erase(it);
        }
        delete t;
    }

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
}

bool Minigame::isDone() const {
    return _done;
}

bool Minigame::survived() const {
    return _survived;
}

void Minigame::reset() {
    _done = false;
    _survived = false;
    // Reinit threats if needed
}
