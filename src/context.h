#ifndef CONTEXT_H
#define CONTEXT_H

#include "IObjectLogic.h"
#include "ITerrainLogic.h"
#include <memory>

class Context {
private:
    std::unique_ptr<IObjectLogic> _object;
    std::unique_ptr<ITerrainLogic> _terrain;
public:
    Context(std::unique_ptr<IObjectLogic> &&object,std::unique_ptr<ITerrainLogic> &&terrain)
    : _object(std::move(object)), _terrain(std::move(terrain)) {};

    void setObject(std::unique_ptr<IObjectLogic> &&new_object) {
        _object = std::move(new_object);
    };

    void setTerrain(std::unique_ptr<ITerrainLogic> &&new_terrain) {
        _terrain = std::move(new_terrain);
    };
};


#endif