#ifndef LIZARD_RESOURCEMANAGER
#define LIZARD_RESOURCEMANAGER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

class ResourceManager {
public:
    ResourceManager(SDL_Renderer *renderer);
    ~ResourceManager();

    SDL_Texture *getTexture(std::string name);
    Mix_Music *getMusic(std::string name);
    Mix_Chunk *getChunk(std::string name);
    SDL_Texture *getFont(std::string fontName, std::string text);
    std::string getLevel(std::string level);
    SDL_Texture *getDialogue(std::string name);

    void setTextColor(SDL_Color color);

private:
    SDL_Color currColor = {255, 255, 255, 255};
    void cleanup();
    SDL_Renderer *myRenderer;
    void loadImages();
    void loadMusic();
    void loadChunks();
    void loadFonts();
    void loadLevels();
    void loadDialogues();

    std::map<std::string, SDL_Texture *> textures;
    std::map<std::string, Mix_Music *> music;
    std::map<std::string, Mix_Chunk *> chunks;
    std::map<std::string, TTF_Font *> fonts;
    std::map<std::string, std::string> levels;
    std::map<std::string, SDL_Texture *> dialogues;
};
#endif
