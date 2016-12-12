#include "../include/LevelOneInstructState.h"

LevelOneInstructState::LevelOneInstructState(SDL_Renderer *r, int width,
                                             int height, ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    title = resources->getTexture("levelOnePS");

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {0, 0, w, h};
}

int LevelOneInstructState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        if(e->key.keysym.sym == SDLK_SPACE)
            return STATE_GAME;
    }

    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

void LevelOneInstructState::doSound() { return; }

void LevelOneInstructState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void LevelOneInstructState::render(int dt) {

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    SDL_Rect LevelOneInstructD = {600, 470, 500, 250};
    SDL_RenderCopy(renderer, resources->getDialogue("LevelOneInstruct"), NULL, &LevelOneInstructD);

    int supressWarning = dt;
    supressWarning++;
}

void LevelOneInstructState::startMusic(int vol) {
    int t = vol;
    t++;
    return;
}

LevelOneInstructState::~LevelOneInstructState() {
    SDL_DestroyTexture(title);
}
