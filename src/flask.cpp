#include "hero.h"

bool test_inclusion(const std::vector<std::vector<int>>& v1, const std::vector<int>& v2) {
  for (const auto& subvector : v1) {
    if (std::includes(subvector.begin(), subvector.end(), v2.begin(), v2.end())) {
      return true;
    }
  }
  return false;
}

void Flask::interact(Hero * hero) {
    int life_hero = hero->getLife();

    // hero should only be able to use one time a flask


    int x = hero->curr_position[0];
    int y = hero->curr_position[1];
    // hero has already visited this flask?
    bool is_already_visited = test_inclusion(hero->flasks_visited,std::vector<int>{x,y});    

    if(!is_already_visited){
        hero->flasks_visited.push_back(std::vector<int>{x,y});
        life_hero += 3;
        if (life_hero > 20) {
          hero->setLife(20);
        } else {
          hero->setLife(life_hero);
        }
        hero->getCamera()->lightColor = glm::vec3(0.7f,0.7f,1.0f);
        hero->type_timer = FLASK_TIMER;
    } 
};