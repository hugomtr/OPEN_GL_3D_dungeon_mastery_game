#include "hero.h"

void Rosetta::interact(Hero * hero){
    Map* map = Map::getInstance();
    const std::vector<int> coords_exit = map->coords_exit;
    
    // open the exit
    map->getMap()[coords_exit[0]][coords_exit[1]] = 42;

    hero->getCamera()->lightColor = glm::vec3(0.7f,1.0f,0.7f);
    hero->type_timer = ROSETTA_TIMER;
};