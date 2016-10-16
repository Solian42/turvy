#ifndef LIZARD_XMLPARSER
#define LIZARD_XMLPARSER

#include "PlatformObject.h"
#include "SpikesObject.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <SDL.h>

class XmlParser {
	
public:
	XmlParser();
	~XmlParser();

	std::vector<std::pair<std::string, SDL_Rect>> parsedPlatforms;
	std::vector<std::pair<std::string,
		std::vector<int>>> parsedSpikes;
	std::string startTag;
	std::string objName;
	std::ifstream infile;
	
private:
	void parse(std::string startTag);
	
	std::string singleTagHandler();
};

#endif
