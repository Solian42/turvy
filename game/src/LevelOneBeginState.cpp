#include "../include/LevelOneBeginState.h"

LevelOneBeginState::LevelOneBeginState(SDL_Renderer *r, int width, int height,
                                       ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    title = resources->getFont("manaspc80", titleTitle);
    ready = resources->getFont("manaspc60", readyTitle);
    dialogue = resources->getFont("manaspc60", dialogueTitle);
    instructions = resources->getFont("manaspc60", instructionsTitle);

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {(this->width - w) / 2, (int)floor(height * 0.20), w, h};

    SDL_QueryTexture(ready, NULL, NULL, &w, &h);
    readyRect = {(this->width - w) / 2, (int)floor(height * 0.40), w, h};

    SDL_QueryTexture(dialogue, NULL, NULL, &w, &h);
    dialogueRect = {(this->width - w) / 2, (int)floor(height * 0.60), w, h};

    SDL_QueryTexture(instructions, NULL, NULL, &w, &h);
    instructionsRect = {(this->width - w) / 2, (int)floor(height * 0.80), w, h};
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

    if (SDL_RenderCopy(renderer, ready, NULL, &readyRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, dialogue, NULL, &dialogueRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, instructions, NULL, &instructionsRect) < 0) {
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
    SDL_DestroyTexture(ready);
    SDL_DestroyTexture(dialogue);
    SDL_DestroyTexture(instructions);
}
