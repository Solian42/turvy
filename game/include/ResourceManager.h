#ifndef LIZARD_RESOURCEMANAGER
#define LIZARD_RESOURCEMANAGER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

class ResourceManager {
public:
    ResourceManager(SDL_Renderer *renderer);
    ~ResourceManager();

    SDL_Texture *getTexture(std::string name);
    Mix_Music *getMusic(std::string name);
    Mix_Chunk *getChunk(std::string name);
    SDL_Texture *getFont(std::string fontName, std::string text,
                         SDL_Color color);
    std::string getLevel(std::string level);

private:
    void cleanup();
    SDL_Renderer *myRenderer;
    void loadImages();
    void loadMusic();
    void loadChunks();
    void loadFonts();
    void loadLevels();

    std::map<std::string, SDL_Texture *> textures;
    std::map<std::string, Mix_Music *> music;
    std::map<std::string, Mix_Chunk *> chunks;
    std::map<std::string, TTF_Font *> fonts;
    std::map<std::string, std::string> levels;
};

#endif
