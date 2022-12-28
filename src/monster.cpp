#include "monster.h"

bool Monster::can_see_hero(std::vector<int> & hero_position){
    Map * map = Map::getInstance();
    std::vector<std::vector<int>> maze = map->getMap();

    bool row_condition = ((hero_position[0] == curr_position[0]) && (std::abs(hero_position[0] - curr_position[0]) <= 5));
    bool col_condition = ((hero_position[1] == curr_position[1]) && (std::abs(hero_position[1] - curr_position[1]) <= 5));

    if (!row_condition && !col_condition) // not (row_cond or col_cond)
        return false;

    if (row_condition && (curr_position[1] < hero_position[1])){
        for (int j = curr_position[1]; j < hero_position[1]; j++){
            if (maze[curr_position[0]][j] == 0) {
                return false;
            }
        }
    } else if (row_condition && (curr_position[1] > hero_position[1])){
        for (int j = hero_position[1]; j < curr_position[1]; j++){
            if (maze[curr_position[0]][j] == 0) {
                return false;
            }
        }
    } else if (col_condition && (curr_position[0] < hero_position[0])){
        for (int i = curr_position[0]; i < hero_position[0]; i++){
            if (maze[i][curr_position[1]] == 0) {
                return false;
            }
        }
    } else if (col_condition && (curr_position[0] > hero_position[0])){
        for (int i = hero_position[0]; i < curr_position[0]; i++){
            if (maze[i][curr_position[1]] == 0) {
                return false;
            }
        }
    }
    return true;
}

void Monster::find_direction(std::vector<int> & hero_position){
    std::vector<int> direction;
    if ((hero_position[0] == hero_position[0]) && (curr_position[1] < hero_position[1])){
        direction.push_back(0);
        direction.push_back(1);
    } else if ((hero_position[0] == hero_position[0]) && (curr_position[1] > hero_position[1])){
        direction.push_back(0);
        direction.push_back(-1);
    } else if ((hero_position[1] == hero_position[1]) && (curr_position[0] < hero_position[0])){
        direction.push_back(1);
        direction.push_back(0);
    } else if ((hero_position[1] == hero_position[1]) && (curr_position[0] > hero_position[0])){
        direction.push_back(-1);
        direction.push_back(0);
    }
}

void Monster::process_movement(std::vector<int> & hero_position) {
    this->find_direction(hero_position);

    std::vector<int> new_position;
    new_position.push_back(curr_position[0] + direction[0]);
    new_position.push_back(curr_position[1] + direction[1]);

    Map * map = Map::getInstance();
    std::vector<std::vector<int>> maze = map->getMap();

    maze[curr_position[0]][curr_position[1]] = 1;
    maze[new_position[0]][new_position[1]] = 3;

    curr_position = new_position;    
};

void Monster::process_turn() {
    Hero * hero = Hero::getInstance();
    std::vector<int> hero_position = hero->curr_position;
    
    bool can_see_hero = this->can_see_hero(hero_position);

    if (can_see_hero){ 
        this->process_movement(hero_position);
        // send to hero the identity of the monster that pursue him for optimizing purpose
        hero->monster = this;
    }

    bool can_attack_hero = can_see_hero && (std::abs(hero_position[0] - curr_position[0]) <= 1) || (std::abs(hero_position[1] - curr_position[1]) <= 1);
    if (can_attack_hero){
        weapon->attack(hero);
    }
};