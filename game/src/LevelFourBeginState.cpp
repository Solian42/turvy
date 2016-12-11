#include "../include/LevelFourBeginState.h"

LevelFourBeginState::LevelFourBeginState(SDL_Renderer *r, int width, int height,
                                         ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    title = resources->getTexture("levelFourLetter");

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {0, 0, w, h};

}

int LevelFourBeginState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        return STATE_GAME;
    }

    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

void LevelFourBeginState::doSound() { return; }

void LevelFourBeginState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void LevelFourBeginState::render(int dt) {

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    int supressWarning = dt;
    supressWarning++;
}

void LevelFourBeginState::startMusic(int vol) {
    int t = vol;
    t++;
    return;
}

LevelFourBeginState::~LevelFourBeginState() {
    SDL_DestroyTexture(title);

}
