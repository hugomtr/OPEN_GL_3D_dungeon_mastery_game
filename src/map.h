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
};

#endif