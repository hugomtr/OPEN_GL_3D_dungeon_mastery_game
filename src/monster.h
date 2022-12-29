#ifndef MONSTER_H
#define MONSTER_H

#include "actor.h"
#include "hero.h"

class Monster : public Actor {
public:
    std::vector<int> initial_position;
    std::vector<int> direction;
    Monster(std::vector<int>&& _initial_position) {
        initial_position = std::move(_initial_position);
        weapon = std::make_unique<Cudgel>();
        life = 12;
        curr_position = initial_position;
    }  
    bool is_dead = false;
    
    void can_hear_hero();

    void process_turn() override;

    void process_movement(std::vector<int> & hero_position);

    void find_direction(std::vector<int> & hero_position);

    bool can_see_hero(std::vector<int> & hero_position);

    void die();
};

void deleteMonster(std::vector<Monster>& monsters_list, const std::vector<int>& _initial_postion);

#endif