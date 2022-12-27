#ifndef HERO_H
#define HERO_H

#include "actor.h"

class Hero : public Actor {
    Camera camera;
    Context context;
public:
    void attack(){
    };
};

#endif