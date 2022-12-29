#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

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
public:
    Sword(){
        stamina_needed = 0.5f;
    }

    void attack(Actor * actor) override {
        int life_actor = actor->getLife();
        life_actor -= damage;
        std::cout << "hero attack";
        actor->setLife(life_actor);
    };
};

class Cudgel : public IWeapon {
    int damage = 5;
public:
    Cudgel(){
        stamina_needed = 0.9f;
    }

    void attack(Actor * actor) {
        int life_actor = actor->getLife();
        life_actor -= damage;
        actor->setLife(life_actor);
    };
};

#endif