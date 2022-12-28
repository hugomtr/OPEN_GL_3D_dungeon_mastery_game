#include "hero.h"

void Rosetta::interact(Hero * hero){
    Map* map = Map::getInstance();
    const std::vector<int> coords_exit = map->coords_exit;
    
    // open the exit
    map->getMap()[coords_exit[0]][coords_exit[1]] = 42;
    std::cout << " gate are now open" << map->getMap()[coords_exit[0]][coords_exit[1]] << std::endl;
    // render green color during 3s  
};