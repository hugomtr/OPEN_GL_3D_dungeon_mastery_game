#ifndef ACTOR_H
#define ACTOR_H

#include <vector>

#include "map.h"
#include "camera.h"
#include "context.h"

class Actor {
protected:
    std::vector<int> curr_position;
public:
    int life;
    virtual void process_movement(){};
    virtual void attack() = 0;
    void removeLife(int life_remove){life -= life_remove;};
};

#endif