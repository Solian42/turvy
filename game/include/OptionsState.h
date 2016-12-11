//
//  OptionsState.hpp
//  game
//
//  Created by Tristan Orton-Urbina on 12/11/16.
//  Copyright © 2016 lizard. All rights reserved.
//

#ifndef OPTIONS_STATE_LIZARD
#define OPTIONS_STATE_LIZARD
#include "State.h"

class OptionsState : public State {
public:
    int getMyState() { return STATE_OPTIONS; }
    OptionsState(SDL_Renderer *r, int width, int height, ResourceManager *res, SDL_Window * window, int *volume);
    int handleEvent(SDL_Event *e, int dt);
    void doSound();
    void doPhysics(int dt);
    void render(int dt);
    void startMusic(int vol);
    
    ~OptionsState();
    
private:
    const int MAX_VOLUME = 128;
    const int MAX_BRIGHTNESS = 100;
    SDL_Window * myWindow;
    int * masterVol;
    int currBright = 50;
    int currSelect = 0;
    int width, height;
    int time = 0;
    int editing = 0;
    
    SDL_Texture *title = NULL;
    SDL_Rect titleRect;
    
    SDL_Texture *audio[2] = {NULL, NULL};
    SDL_Rect audioRect;
    
    SDL_Texture *bright[2] = {NULL, NULL};
    SDL_Rect brightRect;
    
    SDL_Texture *quitGame[2] = {NULL, NULL};
    SDL_Rect quitGameRect;
    
    SDL_Texture *navigation = nullptr;
    SDL_Rect navigationRect;
    
    std::string titleTitle = "Options";
    std::string audioTitle = "Volume: 64";
    std::string brightnessTitle = "Brightness: 50";
    std::string quitGameTitle = "Main Menu";
    std::string navigationTitle = "[Up/Down] to navigate, [Enter] to select, [Left/Right] to change values.";
    SDL_Renderer *renderer;
    
};

#endif /* OptionsState_h */
