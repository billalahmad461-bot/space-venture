#ifndef SPACESHIP_H
#define SPACESHIP_H

#include <string>
#include <vector>
#include "crew.h"
#include "weapon.h"
#include "shield.h"
#include "region.h"
#include "planet.h"
#include "resource.h"
#include <SFML/Graphics.hpp>

class Spaceship {
private:
    std::string _name;
    std::vector<Crew*> _crew;
    Weapon* _weapon;
    Shield* _shield;
    int _equipment_lvl;
    Region* _region;
    Planet* _current_planet;
    int _fuel;
    int _money;
    std::vector<Resource*> _cargo;
    sf::Sprite _sprite_top;
    sf::Sprite _sprite_main;
    sf::Vector2f _position;
    sf::Vector2f _velocity;

public:
    Spaceship(std::string name);
    ~Spaceship();
    void travel(Region* d_region, Planet* d_planet);
    void encounterPirates(Region* c_region);
    void encounterAsteroids(Region* c_region);
    void collectResources(std::string resource, int miners, int equipment_lvl);
    void manageResources();
    void sellResource(std::string type, int amount);
    void addCrew(Crew* crew);
    int countMiners() const;
    int countEngineers() const;
    Weapon* getWeapon() const;
    Shield* getShield() const;
    int getEquipmentLvl() const;
    void setEquipmentLvl(int lvl);
    Planet* getCurrentPlanet() const;
    Region* getRegion() const;
    int getFuel() const;
    void setFuel(int fuel);
    int getMoney() const;
    void setMoney(int money);
    std::vector<Resource*> getCargo() const;
    const std::vector<Crew*>& getCrew() const;
    void loadSprites();
    const sf::Sprite& getSpriteTop() const;
    const sf::Sprite& getSpriteMain() const;
    sf::Vector2f getPosition() const;
    void setPosition(sf::Vector2f pos);
    void update(float delta);
    void shoot(std::vector<Bullet*>& bullets);
    void setRegion(Region* region);
    void setCurrentPlanet(Planet* planet);
    void setVelocity(sf::Vector2f velocity);
    bool consumeResource(std::string type, int amount);
};

#endif
