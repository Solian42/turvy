#include "../include/XmlParser.h"

XmlParser::XmlParser(std::string filename) {

    infile.open(filename, std::ifstream::in);
    std::string waste;
    startTag = "";
    objName = "unknown";
    infile >> waste;
    while (infile >> startTag) {
        parse(startTag);
    }
    infile >> waste;
    infile.close();
}

void XmlParser::parse(std::string startTag) {
    std::string garbage;
    if (startTag.compare("<platforms>") == 0 ||
        startTag.compare("<spikes>") == 0 ||
        startTag.compare("<checkpoints>") == 0 ||
        startTag.compare("<coins>") == 0 ||
        startTag.compare("<trampolines>") == 0 ||
        startTag.compare("<enemies>") == 0 ||
        startTag.compare("<teleports>") == 0 ||
        startTag.compare("<dialogues>") == 0) {
        infile >> garbage;
        objName = startTag;
    } else if (startTag.compare("</platforms>") == 0 ||
               startTag.compare("</spikes>") == 0 ||
               startTag.compare("</checkpoints>") == 0 ||
               startTag.compare("</coins>") == 0 ||
               startTag.compare("</trampolines>") == 0 ||
               startTag.compare("</enemies>") == 0 ||
               startTag.compare("</teleports>") == 0 ||
               startTag.compare("</dialogues>") == 0) {
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
        int h = std::stoi(singleTagHandler());
        int direction = std::stoi(singleTagHandler());
        std::string textureName = singleTagHandler();

        std::vector<int> xydir;
        xydir.push_back(x);
        xydir.push_back(y);
        xydir.push_back(w);
        xydir.push_back(h);
        xydir.push_back(direction);
        parsedSpikes.push_back(std::make_pair(textureName, xydir));
    } else if (objName.compare("<checkpoints>") == 0) {
        int x = std::stoi(singleTagHandler());
        int y = std::stoi(singleTagHandler());
        std::vector<std::string> textureNames = {singleTagHandler(),
                                                 singleTagHandler()};

        std::vector<int> xy;
        xy.push_back(x);
        xy.push_back(y);
        parsedCheckpoints.push_back(std::make_pair(textureNames, xy));
    } else if (objName.compare("<coins>") == 0) {
        int x = std::stoi(singleTagHandler());
        int y = std::stoi(singleTagHandler());
        std::string textureName = singleTagHandler();

        std::vector<int> xy;
        xy.push_back(x);
        xy.push_back(y);
        parsedCoins.push_back(std::make_pair(textureName, xy));
    } else if (objName.compare("<trampolines>") == 0) {
        int x = std::stoi(singleTagHandler());
        int y = std::stoi(singleTagHandler());
        int w = std::stoi(singleTagHandler());
        std::string textureName = singleTagHandler();

        std::vector<int> xy;
        xy.push_back(x);
        xy.push_back(y);
        xy.push_back(w);
        parsedTrampolines.push_back(std::make_pair(textureName, xy));
    } else if (objName.compare("<enemies>") == 0) {
        int x = std::stoi(singleTagHandler());
        int y = std::stoi(singleTagHandler());
        int direction = std::stoi(singleTagHandler());
        std::vector<std::string> textureNames = {
            singleTagHandler(), singleTagHandler(), singleTagHandler(),
            singleTagHandler()};

        std::vector<int> xydir;
        xydir.push_back(x);
        xydir.push_back(y);
        xydir.push_back(direction);
        parsedEnemies.push_back(std::make_pair(textureNames, xydir));
    } else if (objName.compare("<teleports>") == 0) {
        int x = std::stoi(singleTagHandler());
        int y = std::stoi(singleTagHandler());
        int newX = std::stoi(singleTagHandler());
        int newY = std::stoi(singleTagHandler());
        std::vector<std::string> textureNames = {
            singleTagHandler(), singleTagHandler(), singleTagHandler()};

        std::vector<int> teleXY;
        teleXY.push_back(x);
        teleXY.push_back(y);
        teleXY.push_back(newX);
        teleXY.push_back(newY);
        parsedTeleports.push_back(std::make_pair(textureNames, teleXY));
    } else if (objName.compare("<dialogues>") == 0) {
        int x = std::stoi(singleTagHandler());
        int y = std::stoi(singleTagHandler());
        int w = std::stoi(singleTagHandler());
        int h = std::stoi(singleTagHandler());
        std::string textureName = singleTagHandler();

        std::vector<int> dim;
        dim.push_back(x);
        dim.push_back(y);
        dim.push_back(w);
        dim.push_back(h);
        parsedDialogues.push_back(std::make_pair(textureName, dim));
    }

    infile >> garbage;
}

std::string XmlParser::singleTagHandler() {
    std::string str;
    std::string garbage;
    infile >> garbage >> str >> garbage;
    return str;
}

XmlParser::~XmlParser() {}
