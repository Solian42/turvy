#ifndef LIZARD_MAIN
#define LIZARD_MAIN

#include "EnemyObject.h"
#include "GameState.h"
#include "HighScoreState.h"
#include "LevelEditor.h"
#include "LevelFourBeginState.h"
#include "LevelOneBeginState.h"
#include "LevelOneInstructState.h"
#include "LevelThreeBeginState.h"
#include "LevelTwoBeginState.h"
#include "MainMenuState.h"
#include "OptionsState.h"
#include "PlayerObject.h"
#include "State.h"
#include "TitleState.h"
#include "WinState.h"
#include "World.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <vector>

void printFPS(std::chrono::duration<double> dtNano);
void load();
void run();
void cleanup();
void setup(const char *title);

const int width = 1280;
const int height = 720;
int highScore = -1;
SDL_Window *mainWindow;
SDL_Renderer *mainRenderer;
ResourceManager *resources;
#endif
