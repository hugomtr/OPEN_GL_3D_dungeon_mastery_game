#include "hero.h"

Hero* Hero::hero = nullptr;

Hero* Hero::getInstance(){
    if (hero == nullptr){
        Camera * _camera = Camera::getInstance();
        hero = new Hero(_camera);
    }
    return hero;
}

void Hero::setWeapon(std::unique_ptr<IWeapon> &&new_weapon) {
    weapon = std::move(new_weapon);
};

void Hero::setTerrain(std::unique_ptr<ITerrainLogic> &&new_terrain) {
    terrain = std::move(new_terrain);
};

void Hero::process_turn(){
    // retrieve index of the case according  
    float x = camera->Front[0];
    float y = camera->Front[2];        
    
    x += curr_position[0];
    y += curr_position[1];
    
    if ((x < 30) && (y < 30) && (x >= 0) && (y >= 0)){
        curr_position[0] = x;
        curr_position[1] = y;
    }

    Map* map = Map::getInstance();
    std::vector<std::vector<int>> maze = map->getMap();


    std::cout << "call " <<  curr_position[0] << " " << curr_position[1] << " "<< std::endl;

    int value = maze[curr_position[0]][curr_position[1]];
    switch (value)
    {
    case 4:
        // Flask
        this->setTerrain(std::make_unique<Flask>());
        terrain->interact(this);
        break;
    case 5:
        // Lava
        this->setTerrain(std::make_unique<Lava>());
        terrain->interact(this);
        break;
    case 2:
        // Rosetta
        this->setTerrain(std::make_unique<Rosetta>());
        terrain->interact(this);
        break;
    case 42:
        // Exit
        this->setTerrain(std::make_unique<Exit>());
        terrain->interact(this);    
        break;
    default:
        break;
    }

    //std::cout << "life : " << this->life << std::endl;

    if (should_change_weapon){
        if (weapon_type == SWORD){
            weapon_type = CUDGEL;
            this->setWeapon(std::make_unique<Cudgel>());
        } else {
            weapon_type = SWORD;
            this->setWeapon(std::make_unique<Sword>());
        }
    }

    // should attack must actiavte by a command of the user
    if (should_attack){ 
        weapon->attack(monster);
    }

}
