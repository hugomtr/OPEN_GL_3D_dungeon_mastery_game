#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

#include "sound.h"

class IWeapon;

class Actor {
protected:
    std::unique_ptr<IWeapon> weapon;
    int life;
public:
    std::vector<int> curr_position;
    virtual void process_turn(){};
    void removeLife(int life_remove){life -= life_remove;};
    void setLife(int _life) {life = _life;};
    int getLife(){return this->life;}
};

class IWeapon {
    int damage;
public:
    float stamina_needed;
    virtual void attack(Actor * actor) = 0;
};

class Sword : public IWeapon {
    int damage = 3;
    Sound * sword_sound = new Sound("../ressources/music/sword_hit.wav");
public:
    Sword(){
        stamina_needed = 0.25f;
    }

    void attack(Actor * actor) override {
        sword_sound->play();
        int life_actor = actor->getLife();
        life_actor -= damage;
        std::cout << "hero attack";
        actor->setLife(life_actor);
    };
};

class Cudgel : public IWeapon {
    int damage = 5;
    Sound * cudgel_sound = new Sound("../ressources/music/cudgel_hit.wav");
public:
    Cudgel(){
        stamina_needed = 0.5f;
    }

    void attack(Actor * actor) {
        cudgel_sound->play();
        int life_actor = actor->getLife();
        life_actor -= damage;
        actor->setLife(life_actor);
    };
};

#endif