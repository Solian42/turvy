#include "../include/XmlParser.h"

XmlParser::XmlParser(){
	infile.open("../data/text/level.xml");
	std::string waste;
	startTag = "";
	objName = "unknown";
	infile >> waste;
	while (infile >> startTag){
		parse(startTag);
	}
	infile >> waste;
}

void XmlParser::parse(std::string startTag){
	std::string garbage;
	if(startTag.compare("<Platform>") == 0 || startTag.compare("<Spike>") == 0){
		objName = startTag;
	} else if (startTag.compare("</Platform>") == 0 || startTag.compare("</Spike>") == 0){
		objName = "unknown";
	}

	infile >> garbage;
	if(objName.compare("<Platform>") == 0){
		int x = std::stoi(singleTagHandler());
		int y = std::stoi(singleTagHandler());
		int w = std::stoi(singleTagHandler());
		int h = std::stoi(singleTagHandler());
		std::string textureName = singleTagHandler();
		
		parsedPlatforms.push_back(new Platform(x, y, w, h, textureName));
	} else if(objName.compare("<Spike>") == 0){
		int x = std::stoi(singleTagHandler());
		int y = std::stoi(singleTagHandler());
		std::string direction = singleTagHandler();
		std::string textureName = singleTagHandler();

		parsedSpikes.push_back(new Spike(x, y, direction, textureName));
	} else {
		std::cout << "unidentified objName!";
	}
	infile >> garbage;
}

std::string XmlParser::singleTagHandler(){
	std::string str;
	std::string garbage;
	infile >> garbage >> str >> garbage;
	return str.substr(1, str.length() - 2);
}

XmlParser::~XmlParser() {

}
