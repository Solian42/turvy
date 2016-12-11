#include "../include/LevelTwoBeginState.h"

LevelTwoBeginState::LevelTwoBeginState(SDL_Renderer *r, int width, int height,
                                       ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    title = resources->getTexture("levelTwoLetter");

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {0, 0, w, h};
}

int LevelTwoBeginState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        if(e->key.keysym.sym == SDLK_SPACE)
            return STATE_GAME;
    }

    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

void LevelTwoBeginState::doSound() { return; }

void LevelTwoBeginState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void LevelTwoBeginState::render(int dt) {

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    int supressWarning = dt;
    supressWarning++;
}

void LevelTwoBeginState::startMusic(int vol) {
    int t = vol;
    t++;
    return;
}

LevelTwoBeginState::~LevelTwoBeginState() {
    SDL_DestroyTexture(title);

}
