#include "../include/TitleState.h"

TitleState::TitleState(SDL_Renderer *r, int width, int height,
                       ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    
///////
    splash = resources->getTexture("intro");

    splashRect = {0, 0, width, height};
    SDL_SetTextureAlphaMod(splash, 0);
///////
}

int TitleState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        Mix_HaltMusic();
        return STATE_MAINMENU;
    }
    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}
void TitleState::doSound() { return; }
void TitleState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void TitleState::render(int dt) {
    time += dt;
    while (time > 64) {
        time -= 64;
        // if (splashAlpha < 255 && !fadein) {
        //     splashAlpha++;
        //     if(splashAlpha >= 255) fadein = true;
        //     SDL_SetTextureAlphaMod(splash, splashAlpha);
        // } else {
        //     // if (splashAlpha > 10) {
        //     //     fadein = true;
        //     //     splashAlpha = splashAlpha - 5;
        //     // }
        // }
        if(!fadein){
            if(splashAlpha < 255){
                splashAlpha++;
                if(splashAlpha < 255) splashAlpha++;
            } else {
                splashAlpha = 255;
                fadein =true;
            }
        }
        SDL_SetTextureAlphaMod(splash, splashAlpha);
    }

    if (SDL_RenderCopy(renderer, splash, NULL, &splashRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }
}
void TitleState::startMusic(int vol) {
    Mix_PlayMusic(resources->getMusic("title"), 1);
    Mix_VolumeMusic(vol);
    return;
}

double radToDegs(double r) { return r * M_PI / 180; }

TitleState::~TitleState() {
    SDL_DestroyTexture(splash);
}
