#ifndef LIZARD_RESOURCEMANAGER
#define LIZARD_RESOURCEMANAGER

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <map>
#include <iostream>
#include <fstream>

class ResourceManager {
public:
	ResourceManager(SDL_Renderer *renderer);
	
	SDL_Texture * getTexture(std::string name);
	Mix_Music * getMusic(std::string name);
	Mix_Chunk * getChunk(std::string name);
	TTF_Font * getFont(std::string name);
	
	void cleanup();
private:
	SDL_Renderer *myRenderer;
	void loadImages();
	void loadMusic();
	void loadChunks();
	void loadFonts();
	
	std::map<std::string, SDL_Texture *> textures;
	std::map<std::string, Mix_Music *> music;
	std::map<std::string, Mix_Chunk *> chunks;
	std::map<std::string, TTF_Font *> fonts;
};

#endif
