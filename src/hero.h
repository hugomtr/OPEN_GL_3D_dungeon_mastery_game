#ifndef HERO_H
#define HERO_H

#include "actor.h"
#include "camera.h"
#include "map.h"

#include "monster.h"

enum WEAPON_TYPE {
    SWORD,
    CUDGEL,
};

#define MONSTER_ATTACK_TIMER 2;
#define LAVA_TIMER 16;
#define FLASK_TIMER 6;
#define ROSETTA_TIMER 8;

class Monster;
class ITerrainLogic;

/* Singleton Pattern */
class Hero : public Actor {
protected:
    Camera * camera;
    std::unique_ptr<ITerrainLogic> terrain;
    Hero(Camera * _camera) {
        camera = _camera;
        curr_position = camera->cameraMapCoordinates;
        weapon = std::make_unique<Sword>();
        life = 20;
    }    
    static Hero * hero;
public:
    WEAPON_TYPE weapon_type = SWORD;
    std::vector<std::vector<int>> flasks_visited;
    Monster * monster;
    static int ANIMATION_TIMER;
    static float STAMINA;
    int type_timer = 0;
    Sound * die_sound = new Sound("../ressources/music/die.wav");
    bool is_dead = false;    
    void incrementTimer(int type_timer);
    
    Hero(Hero & _other) = delete;

    void operator=(Hero & _other) = delete;

    static Hero * getInstance();

    void setWeapon(std::unique_ptr<IWeapon> &&new_weapon);
    std::unique_ptr<IWeapon>& getWeapon();

    void attack_monster();

    void should_change_weapon();

    void setTerrain(std::unique_ptr<ITerrainLogic> &&new_terrain);
    
    void change_attributes_according_to_life();// update vision_coeff attributes according to life

    void process_turn();

    void process_input_user();

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