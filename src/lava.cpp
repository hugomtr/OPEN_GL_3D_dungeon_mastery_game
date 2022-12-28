#include "hero.h"

void Lava::interact(Hero * _hero) {
    int life_hero = _hero->getLife();
    life_hero -= 5;
    _hero->setLife(life_hero);

    if (life_hero <= 0) {
        // renderer.terminate 
        // and then terminate program
    } 
    _hero->getCamera()->lightColor = glm::vec3(1.0f,0.5f,0.5f);
    // renderer.time_attributes = 5; // attributes from renderer that say how much time renderer need to render by this attributes
};