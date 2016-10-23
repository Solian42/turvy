#ifndef LIZARD_XMLPARSER
#define LIZARD_XMLPARSER

#include "PlatformObject.h"
#include "SpikesObject.h"
#include "CheckpointObject.h"
#include <SDL.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

class XmlParser {

public:
    XmlParser();
    ~XmlParser();

    std::vector<std::pair<std::string, SDL_Rect>> parsedPlatforms;
    std::vector<std::pair<std::string, std::vector<int>>> parsedSpikes;
    std::vector<std::pair<std::string, std::vector<int>>> parsedCheckpoints;
    std::string startTag;
    std::string objName;
    std::ifstream infile;

private:
    void parse(std::string startTag);

    std::string singleTagHandler();
};

#endif
