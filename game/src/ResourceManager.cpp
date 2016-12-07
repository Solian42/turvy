#include "../include/ResourceManager.h"

ResourceManager::ResourceManager(SDL_Renderer *renderer) {
    myRenderer = renderer;
    textures = std::map<std::string, SDL_Texture *>();
    music = std::map<std::string, Mix_Music *>();
    chunks = std::map<std::string, Mix_Chunk *>();
    fonts = std::map<std::string, TTF_Font *>();
    levels = std::map<std::string, std::string>();
    loadImages();
    loadMusic();
    loadChunks();
    loadFonts();
    loadLevels();
}

void ResourceManager::loadImages() {
    std::ifstream infile;

    infile.open("../data/images/imageResources.data", std::ifstream::in);

    std::string name = "";
    std::string filename = "";
    SDL_Surface *image = nullptr;
    while (infile >> name >> filename) {
        image = IMG_Load(filename.c_str());
        if (!image) {
            std::cout << "IMG_Load: " << IMG_GetError() << "\n";
        }
        SDL_Texture *text = SDL_CreateTextureFromSurface(myRenderer, image);
        textures[name] = text;
        SDL_FreeSurface(image);
    }
    infile.close();
}

void ResourceManager::loadMusic() {
    std::ifstream infile;

    infile.open("../data/sounds/musicResources.data", std::ifstream::in);

    std::string name = "";
    std::string filename = "";

    while (infile >> name >> filename) {
        music[name] = Mix_LoadMUS(filename.c_str());
        if (music[name] == NULL) {
            std::cout << "Failed to load " << filename
                      << " music! SDL_mixer Error: " << Mix_GetError() << "\n";
        }
    }
}

void ResourceManager::loadChunks() {
    std::ifstream infile;

    infile.open("../data/sounds/chunkResources.data", std::ifstream::in);

    std::string name = "";
    std::string filename = "";

    while (infile >> name >> filename) {
        chunks[name] = Mix_LoadWAV(filename.c_str());
        if (chunks[name] == NULL) {
            std::cout << "Failed to load " << filename
                      << " sound effect! SDL_mixer Error: " << Mix_GetError()
                      << "\n";
        }
    }
    infile.close();
}

void ResourceManager::loadFonts() {
    std::ifstream infile;

    infile.open("../data/fonts/fontResources.data", std::ifstream::in);

    std::string name = "";
    std::string filename = "";
    int size;

    while (infile >> name >> filename >> size) {
        fonts[name] = TTF_OpenFont(filename.c_str(), size);
        if (fonts[name] == NULL) {
            std::cout << "Failed to load " << filename
                      << " font! SDL_ttf Error: " << TTF_GetError() << "\n";
        }
    }
    infile.close();
}

void ResourceManager::loadLevels() {
    std::ifstream infile;

    infile.open("../data/levels/levels.data", std::ifstream::in);

    std::string name = "";
    std::string filename = "";

    while (infile >> name >> filename) {
        levels[name] = filename;
    }
    infile.close();
}

SDL_Texture *ResourceManager::getTexture(std::string name) {
    return textures[name];
}

Mix_Music *ResourceManager::getMusic(std::string name) { return music[name]; }

Mix_Chunk *ResourceManager::getChunk(std::string name) { return chunks[name]; }

SDL_Texture *ResourceManager::getFont(std::string fontName, std::string text) {
    SDL_Surface *temp =
        TTF_RenderUTF8_Blended(fonts[fontName], text.c_str(), currColor);
    SDL_Texture *temptex = SDL_CreateTextureFromSurface(myRenderer, temp);
    SDL_FreeSurface(temp);
    return temptex;
}

std::string ResourceManager::getLevel(std::string level) {
    return levels[level];
}

void ResourceManager::setTextColor(SDL_Color color) { currColor = color; }

void ResourceManager::cleanup() {
    for (std::pair<std::string, SDL_Texture *> p : textures) {
        SDL_DestroyTexture(p.second);
    }
    for (std::pair<std::string, Mix_Music *> p : music) {
        Mix_FreeMusic(p.second);
    }
    for (std::pair<std::string, Mix_Chunk *> p : chunks) {
        Mix_FreeChunk(p.second);
    }
    for (std::pair<std::string, TTF_Font *> p : fonts) {
        TTF_CloseFont(p.second);
    }
}

ResourceManager::~ResourceManager() { cleanup(); }
