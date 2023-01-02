#include "hero.h"

void Lava::interact(Hero * _hero) {
    int life_hero = _hero->getLife();
    life_hero -= 7;
    _hero->setLife(life_hero);

    if (life_hero <= 0) {
        // renderer.terminate 
        // and then terminate program
    } 
    _hero->getCamera()->lightColor = glm::vec3(1.0f,0.5f,0.5f);
    _hero->type_timer = LAVA_TIMER;

    lava_sound->play();
};