#include "../include/ResourceManager.h"

ResourceManager::ResourceManager(SDL_Renderer *renderer) {
    myRenderer = renderer;
    textures = std::map<std::string, SDL_Texture *>();
    music = std::map<std::string, Mix_Music *>();
    chunks = std::map<std::string, Mix_Chunk *>();
    fonts = std::map<std::string, TTF_Font *>();
    levels = std::map<std::string, std::string>();
    dialogues = std::map<std::string, SDL_Texture *>();
    loadImages();
    loadMusic();
    loadChunks();
    loadFonts();
    loadLevels();
    loadDialogues();
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

void ResourceManager::loadDialogues() {
    std::ifstream infile;

    infile.open("../data/text/dialogues.data", std::ifstream::in);
    std::string string;
    std::string name;
    std::string text;
    std::string firstWord;
    SDL_Texture *background = getTexture("dialoguebgnd");
    TTF_Font *tempFont = TTF_OpenFont("../data/fonts/manaspc.ttf", 20);
    SDL_Color black = {0, 0, 0, 255};

    while (std::getline(infile, string)) {
        std::stringstream ss(string);
        ss >> name >> firstWord;
        std::getline(ss, text);
        text = firstWord + text;
        SDL_Texture *myTexture;
        myTexture = SDL_CreateTexture(myRenderer, SDL_PIXELFORMAT_RGBA8888,
                                      SDL_TEXTUREACCESS_TARGET, 500, 250);
        SDL_SetTextureBlendMode(myTexture, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(myRenderer, 0, 0, 0, 0);
        SDL_SetRenderTarget(myRenderer, myTexture);
        SDL_RenderClear(myRenderer);
        SDL_Rect temp = {0, 0, 500, 250};
        SDL_RenderCopy(myRenderer, background, NULL, &temp);
        SDL_Surface *prerenderedFont =
            TTF_RenderText_Blended_Wrapped(tempFont, text.c_str(), black, 344);
        SDL_Texture *renderedFont =
            SDL_CreateTextureFromSurface(myRenderer, prerenderedFont);
        SDL_FreeSurface(prerenderedFont);
        int w, h;
        SDL_QueryTexture(renderedFont, NULL, NULL, &w, &h);
        SDL_Rect fontRect = {78, 23, w, h};
        SDL_RenderCopy(myRenderer, renderedFont, NULL, &fontRect);
        dialogues[name] = myTexture;
        SDL_DestroyTexture(renderedFont);
    }
    SDL_SetRenderTarget(myRenderer, NULL);
    TTF_CloseFont(tempFont);
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

SDL_Texture *ResourceManager::getDialogue(std::string name) {
    return dialogues[name];
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
