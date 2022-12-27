#ifndef HERO_H
#define HERO_H

#include "actor.h"

class Monster : public Actor {
    std::vector<int> initial_position;
public:
    void attack();
    void can_hear_hero();
    void can_see_hero();
    void process_movement();
};

#endif