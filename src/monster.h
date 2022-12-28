#ifndef MONSTER_H
#define MONSTER_H

#include "actor.h"
#include "hero.h"

class Monster : public Actor {
    std::vector<int> direction;
    static std::vector<Monster> monster_list;
    std::vector<int> initial_position;
public:
    Monster(std::vector<int>&& _initial_position) {
        initial_position = std::move(_initial_position);
        weapon = std::make_unique<Cudgel>();
        life = 8;
    }  
    
    void can_hear_hero();

    void process_turn() override;

    void process_movement(std::vector<int> & hero_position);

    void find_direction(std::vector<int> & hero_position);

    bool can_see_hero(std::vector<int> & hero_position);
};

#endif