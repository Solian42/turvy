//Header file for SDL C++ demo
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <math.h>

const int width = 800;
const int height = 600;
const char * title = "Intro to Video Games";
const double twoPi = 2 * M_PI;
const double radToDeg = 180 / M_PI;


SDL_Window* gWindow;
SDL_Renderer* gRenderer;
SDL_Texture * gTexture;

Mix_Music *gMusic;
TTF_Font *gFont;
TTF_Font *gFont2;

int center(int large, int small);
SDL_Rect * centeredRect(int largeW, int largeH, int smallW, int smallH);
