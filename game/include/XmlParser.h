#ifndef LIZARD_XMLPARSER
#define LIZARD_XMLPARSER

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>


class XmlParser {
public:
	XmlParser();
	~XmlParser();

	std::vector<Platform> parsedPlatforms;
	std::vector<Spike> parsedSpikes;
	std::string startTag;
	std::string objName;
	std::ifstream infile;
}

void XmlParser::parse(std::string startTag);

std::string XmlParser::singleTagHandler();
