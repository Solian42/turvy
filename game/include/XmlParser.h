#ifndef LIZARD_XMLPARSER
#define LIZARD_XMLPARSER

#include "CheckpointObject.h"
#include "CoinObject.h"
#include "EnemyObject.h"
#include "PlatformObject.h"
#include "SpikesObject.h"
#include "TrampolineObject.h"
#include <SDL.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class XmlParser {

public:
    XmlParser(std::string filename);
    ~XmlParser();

    std::vector<std::pair<std::string, SDL_Rect>> parsedPlatforms;
    std::vector<std::pair<std::string, std::vector<int>>> parsedSpikes;
    std::vector<std::pair<std::vector<std::string>, std::vector<int>>>
        parsedCheckpoints;
    std::vector<std::pair<std::string, std::vector<int>>> parsedCoins;
    std::vector<std::pair<std::string, std::vector<int>>> parsedTrampolines;
    std::vector<std::pair<std::vector<std::string>, std::vector<int>>>
        parsedEnemies;
    std::string startTag;
    std::string objName;
    std::ifstream infile;

private:
    void parse(std::string startTag);

    std::string singleTagHandler();
};

#endif
