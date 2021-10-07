#include <iostream>
#include <string>
#include "astar.cpp"

using std::string;

class Map{
private:
    AStar::Generator generator;
    string Mapdatab;
    int width;
    int height;
public:
    Map(string, int, int);

    string algorythm(string);
};
