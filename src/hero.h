#ifndef HERO_H
#define HERO_H

#include "actor.h"
#include "camera.h"
#include "map.h"

#include "monster.h"

enum WEAPON_TYPE {
    SWORD,
    CUDGEL
};
class Monster;
class ITerrainLogic;

class Hero : public Actor {
protected:
    Camera * camera;
    std::unique_ptr<ITerrainLogic> terrain;
    Hero(Camera * _camera) {
        camera = _camera;
        curr_position = camera->cameraMapCoordinates;
        weapon = std::make_unique<Sword>();
        life = 10;
        std::cout << " Hero created" << std::endl;
    }    
    static Hero * hero;
public:
    float vision_coeff = 50.0f;
    WEAPON_TYPE weapon_type = SWORD;
    Hero(Hero & _other) = delete;
    void operator=(Hero & _other) = delete;
    static Hero * getInstance();
    bool should_change_weapon = false;
    bool should_attack = false;
    std::vector<std::vector<int>> flasks_visited;
    Monster * monster;
    
    void setWeapon(std::unique_ptr<IWeapon> &&new_weapon);

    void setTerrain(std::unique_ptr<ITerrainLogic> &&new_terrain);
    
    void change_attributes_according_to_life();// update vision_coeff attributes according to life

    void process_turn();

    Camera * getCamera(){return camera;};
};

class ITerrainLogic {
public:
    virtual void interact(Hero * _hero) = 0;
};

class Lava : public ITerrainLogic {
public:
    void interact(Hero * _hero) override;
};

class Exit : public ITerrainLogic {
public:
    void interact(Hero * _hero) override;
};

class Flask : public ITerrainLogic {
public:
    void interact(Hero * _hero) override;
};

class Rosetta : public ITerrainLogic {
private:
    void interact(Hero * _hero);
};


#endif