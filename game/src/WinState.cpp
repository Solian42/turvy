#include "../include/WinState.h"

WinState::WinState(SDL_Renderer *r, int width, int height,
                                         ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    title = resources->getTexture("reunion");

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {0, 0, w, h};
    SDL_SetTextureAlphaMod(title, 0);

}

int WinState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        if(e->key.keysym.sym == SDLK_SPACE)
            return STATE_HIGHSCORE;
    }

    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

void WinState::doSound() { return; }

void WinState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void WinState::render(int dt) {

    time += dt;
    while (time > 64) {
        time -= 64;
        if (titleAlpha < 255 && !fadein) {
            titleAlpha++;
            fadein = false;
            SDL_SetTextureAlphaMod(title, titleAlpha);
        } else {
            if (titleAlpha > 10) {
                fadein = true;
                titleAlpha = titleAlpha - 5;
            }
        }
    }

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    int supressWarning = dt;
    supressWarning++;
}

void WinState::startMusic(int vol) {
    int t = vol;
    t++;
    return;
}

WinState::~WinState() {
    SDL_DestroyTexture(title);

}
