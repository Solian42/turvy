#include "../include/XmlParser.h"

XmlParser::XmlParser() {

    infile.open("../data/levels/level.xml", std::ifstream::in);
    std::string waste;
    startTag = "";
    objName = "unknown";
    infile >> waste;
    while (infile >> startTag) {
        std::cout << startTag << "\n";
        parse(startTag);
    }
    infile >> waste;
    infile.close();
}

void XmlParser::parse(std::string startTag) {
    std::string garbage;
    if (startTag.compare("<platforms>") == 0 ||
        startTag.compare("<spikes>") == 0) {
        infile >> garbage;
        objName = startTag;
    } else if (startTag.compare("</platforms>") == 0 ||
               startTag.compare("</spikes>") == 0) {
        objName = "unknown";
        return;
    }

    if (objName.compare("<platforms>") == 0) {
        int x = std::stoi(singleTagHandler());
        int y = std::stoi(singleTagHandler());
        int w = std::stoi(singleTagHandler());
        int h = std::stoi(singleTagHandler());
        std::string textureName = singleTagHandler();
        SDL_Rect temp = {x, y, w, h};
        parsedPlatforms.push_back(std::make_pair(textureName, temp));
    } else if (objName.compare("<spikes>") == 0) {
        int x = std::stoi(singleTagHandler());
        int y = std::stoi(singleTagHandler());
        int w = std::stoi(singleTagHandler());
        int direction = std::stoi(singleTagHandler());
        std::string textureName = singleTagHandler();

        std::vector<int> xydir;
        xydir.push_back(x);
        xydir.push_back(y);
        xydir.push_back(w);
        xydir.push_back(direction);
        parsedSpikes.push_back(std::make_pair(textureName, xydir));
    } else {
        std::cout << "unidentified objName!";
    }

    infile >> garbage;
}

std::string XmlParser::singleTagHandler() {
    std::string str;
    std::string garbage;
    infile >> garbage >> str >> garbage;
    return str;
    // return str.substr(1, str.length() - 2);
}

XmlParser::~XmlParser() {}