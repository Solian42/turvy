#include "../include/LevelOneBeginState.h"

LevelOneBeginState::LevelOneBeginState(SDL_Renderer *r, int width, int height,
                                       ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    title = resources->getTexture("levelOneLetter");

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {0, 0, w, h};
}

int LevelOneBeginState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        return STATE_LEVELONEINSTRUCT;
    }

    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

void LevelOneBeginState::doSound() { return; }

void LevelOneBeginState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void LevelOneBeginState::render(int dt) {

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    int supressWarning = dt;
    supressWarning++;
}

void LevelOneBeginState::startMusic(int vol) {
    int t = vol;
    t++;
    return;
}

LevelOneBeginState::~LevelOneBeginState() {
    SDL_DestroyTexture(title);
}
