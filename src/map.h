#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Map {
protected:
    Map(std::vector<std::vector<int>> & _maze): maze(_maze){};
    std::vector<std::vector<int>> maze;
    static Map * map;
public:
    Map(Map & _other) = delete;
    void operator=(Map & _other) = delete;
    static Map * getInstance();
    std::vector<std::vector<int>> & getMap(){return maze;};
    const std::vector<float> coords_rosetta = {28.0f,1.0f};
    const std::vector<int> coords_exit = {29,11};
    float n_rows = static_cast<float>(maze.size());
    float n_columns = static_cast<float>(maze[0].size());
};

#endif