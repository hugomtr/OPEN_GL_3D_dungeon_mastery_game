#include "hero.h"

Hero* Hero::hero = nullptr;

int Hero::ANIMATION_TIMER = 0;

float Hero::STAMINA = 0;

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

std::unique_ptr<IWeapon>& Hero::getWeapon() {
    return weapon;
};

void Hero::setTerrain(std::unique_ptr<ITerrainLogic> &&new_terrain) {
    terrain = std::move(new_terrain);
};

void Hero::process_turn(){
    this->change_attributes_according_to_life();

    if (type_timer > 0){
        this->incrementTimer(type_timer);
    }
}

void Hero::process_input_user(){
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
}

void Hero::should_change_weapon(){
    if (weapon_type == SWORD){
        weapon_type = CUDGEL;
        this->setWeapon(std::make_unique<Cudgel>());
    } else {
        weapon_type = SWORD;
        this->setWeapon(std::make_unique<Sword>());
    }
}

void Hero::attack_monster(){
    if(monster){
        bool ready_to_attack_monster = (std::abs(monster->curr_position[0] - curr_position[0]) <= 1) || (std::abs(monster->curr_position[1] - curr_position[1]) <= 1);
        bool look_in_monster_direction = ((curr_position[0] + camera->Front[0]) == this->monster->curr_position[0]) && ((curr_position[1] + camera->Front[2]) == this->monster->curr_position[1]);
        bool enough_stamina = STAMINA > weapon->stamina_needed;

        //std::cout << "Monster targeted curr position: hero" << curr_position[0] + camera->Front[0] << " " <<curr_position[1] + camera->Front[1]<< "monster: " << this->monster->curr_position[0] << " " << this->monster->curr_position[1] <<std::endl;
        if (ready_to_attack_monster && look_in_monster_direction){
            weapon->attack(monster);
            std::cout << STAMINA <<std::endl;
            STAMINA -= weapon->stamina_needed;
            std::cout << STAMINA <<std::endl;
            //std::cout << "Hero attack Monster Yaa!! with weapon : " << weapon_type << " monster life: " << monster->getLife() << std::endl;
        }
    }
}

void Hero::change_attributes_according_to_life(){
    float lambda = life / 20.0f;
    float value = ( 1.0f - lambda ) * 5.0f + lambda * 25.0f;
    if (life <= 0) {
        value = 3.0;
        is_dead = true;
        die_sound->play();
    }
    camera->vision_coeff = value; 
}

void Hero::incrementTimer(int type_timer){
    if (ANIMATION_TIMER++ > type_timer){
        ANIMATION_TIMER = 0;
        if (!is_dead){
            camera->lightColor = glm::vec3(1.0f);}
        else {
            camera->lightColor = glm::vec3(1.0f,0.5f,0.5f);
        }
    }
}