#ifndef ACTOR_H
#define ACTOR_H

#include <vector>
#include <memory>
#include <algorithm>

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
public:
    virtual void attack(Actor * actor) = 0;
};

class Sword : public IWeapon {
    int damage = 3;
public:
    void attack(Actor * actor) override {
        int life_actor = actor->getLife();
        life_actor -= damage;
        actor->setLife(life_actor);
    };
};

class Cudgel : public IWeapon {
    int damage = 2;
public:
    void attack(Actor * actor) {
        int life_actor = actor->getLife();
        life_actor -= damage;
        actor->setLife(life_actor);
    };
};


#endif