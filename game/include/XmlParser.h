#ifndef LIZARD_XMLPARSER
#define LIZARD_XMLPARSER

#include "PlatformObject.h"
#include "SpikesObject.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <SDL>

class XmlParser {
	
public:
	XmlParser();
	~XmlParser();

	std::vector<std::pair<std::string textureName,
		SDL_Rect platRect> platPair> parsedPlatforms;
	std::vector<std::pair<std::string textureName,
		std::vector<int> spikeList> spikePair> parsedSpikes;
	std::string startTag;
	std::string objName;
	std::ifstream infile;
	
private:
	void parse(std::string startTag);
	
	std::string singleTagHandler();
};

#endif
