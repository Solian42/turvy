/*Very simple SDL demo in C++
* 
* Made by Tristan Orton-Urbina
* tortonu1@jhu.edu for 
* 600.255 FA 2016
* Beware, thar be unchecked errors down here...
*
*/

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <iostream>
#include <cmath>

const int width = 800;
const int height = 600;
const char* title = "Intro to Video Games";
const char* musicTitle = "abstract_tracking.xm";
const double twoPi = 2 * M_PI;
const double radToDeg = 180 / M_PI;


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Texture* gTexture;

Mix_Music* gMusic;
TTF_Font* gFont;
TTF_Font* gFont2;

int center(int large, int small) {

	return large/2 - small/2;
}

double radToDegs(double r) {
	return r * radToDeg;
}

void textureSize(SDL_Texture * t, int* w, int* h) {
	SDL_QueryTexture(t, NULL, NULL, w, h);
	return;
}

// Set up all the basic SDL bits and pieces we'll need.
void setup() {
	
	if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::cerr << "oops. Failed to init: " << SDL_GetError() << "\n";
	}
	
	if( Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 ) {
    	std::cerr <<"SDL_mixer could not initialize! SDL_mixer Error:"
    			  << Mix_GetError() << "\n";
    }
    
   	TTF_Init();
   
   	gWindow = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, 
   							  SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
   	if(gWindow == NULL) {
	   std::cout << "Something broke: " << SDL_GetError();
	}
	
   	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
   	if(gRenderer == NULL) {
	   std::cout << "Something broke: " << SDL_GetError();
	}
	
   	return;
}

void load() {

	int flags=MIX_INIT_OGG|MIX_INIT_MOD;
	int initted=Mix_Init(flags);
	if ( (initted & flags) != flags) {
    	std::cout << "Mix_Init: Failed to init required ogg and mod support!\n" <<
    		"Mix_Init:" << Mix_GetError() << "\n";
    
	}
	
	gMusic = Mix_LoadMUS(musicTitle);
	if (gMusic == NULL) {
		std::cerr <<"SDL_mixer Error:"
    			  << Mix_GetError() << "\n";
    }
	
	SDL_Surface* image = IMG_Load("johns-hopkins-university-logo.png");
	if(!image) {
    	std::cout << "IMG_Load: " << IMG_GetError() << "\n";
	}
	
	gTexture = SDL_CreateTextureFromSurface(gRenderer, image);
	if (gTexture == NULL) {
		std::cout << "Something broke: " << SDL_GetError();
	}
	gFont = TTF_OpenFont("CaesarDressing-Regular.ttf", 72);
	
	gFont2 = TTF_OpenFont("CaesarDressing-Regular.ttf", 74);
	
	return;
}

void cleanup() {
	TTF_CloseFont(gFont2);
	TTF_CloseFont(gFont);
	Mix_FreeMusic(gMusic);
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	TTF_Quit();
	Mix_Quit();
	SDL_Quit();
}

void run() {
	Mix_PlayMusic(gMusic, -1);
	SDL_Event event;
	bool running = true;
	unsigned int lastTime = 0;
	unsigned int currentTime;
	double time = 0.0;
	SDL_Color white = {255,255,255,255};
	SDL_Surface* text = TTF_RenderUTF8_Blended(gFont, title, white);
	SDL_Texture* textex =  SDL_CreateTextureFromSurface(gRenderer, text);
	SDL_Color black ={0,0,0,255};
	SDL_Surface* shadow = TTF_RenderUTF8_Blended(gFont2, title, black);
	SDL_SetSurfaceAlphaMod(shadow, 128);
	SDL_Texture* shadowex =  SDL_CreateTextureFromSurface(gRenderer, shadow);
	int textureW;
	int textureH;
	textureSize(gTexture, &textureW, &textureH);
	SDL_Rect  textureRect = {center(width, textureW), center(height, textureH),
							 textureW, textureH};
	SDL_Rect  shadowRect = {center(width, shadow->w), center(height, shadow->h),
							shadow->w, shadow->h};
	SDL_Rect  textRect = {center(width, text->w), center(height, text->h),
						  text->w, text->h};
	
	while(running) {
		currentTime = SDL_GetTicks();
		unsigned int dt = currentTime - lastTime;
		time += (double) dt / 1000.00;
		lastTime = currentTime;
		
		if( time > twoPi) {
			time -= twoPi;
		}
		
		while(SDL_PollEvent( &event ) != 0) {
			switch(event.type) {
			
			case SDL_QUIT:
				running = false;
				break;
			case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_q || event.key.keysym.sym == SDLK_ESCAPE) {
					running = false;
				}
			}
		
		}
	
		SDL_RenderClear(gRenderer);
		if (SDL_RenderCopyEx(gRenderer, gTexture, NULL, &textureRect,
						 radToDegs(sin(time)), NULL, SDL_FLIP_NONE) < 0) {
			std::cout << "Something broke: " << SDL_GetError();
		}
						 
		if (SDL_RenderCopy(gRenderer, shadowex, NULL, &shadowRect) < 0) {
			std::cout << "Something broke: " << SDL_GetError();
		}
		
		if (SDL_RenderCopy(gRenderer, textex, NULL, &textRect) < 0) {
			std::cout << "Something broke: " << SDL_GetError();
		}
		SDL_RenderPresent(gRenderer);
		
	}
	
	return;
}

int main() {
	setup();
	
	load();
	
	run();
	
	cleanup();
	
	return 0;
}
                                        



	
