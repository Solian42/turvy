#include "../include/LevelThreeBeginState.h"

LevelThreeBeginState::LevelThreeBeginState(SDL_Renderer *r, int width,
                                           int height, ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    title = resources->getTexture("levelThreeLetter");

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {0, 0, w, h};
}

int LevelThreeBeginState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        return STATE_GAME;
    }

    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

void LevelThreeBeginState::doSound() { return; }

void LevelThreeBeginState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void LevelThreeBeginState::render(int dt) {

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    int supressWarning = dt;
    supressWarning++;
}

void LevelThreeBeginState::startMusic(int vol) {
    int t = vol;
    t++;
    return;
}

LevelThreeBeginState::~LevelThreeBeginState() {
    SDL_DestroyTexture(title);
}
