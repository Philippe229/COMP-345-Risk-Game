#ifndef MAP_LOADER_H_
#define MAP_LOADER_H_

#include <string>
#include <fstream>
#include "../Map/Map.h"

class MapLoader {
private:
    Map* loadedMap;
    string readLine(ifstream&);
    string strip(string);
    vector<string> split(string, char);

public:
    MapLoader();
    MapLoader(string);
    ~MapLoader();

    Map* getMap();
    void parseMap(string);
};

#endif