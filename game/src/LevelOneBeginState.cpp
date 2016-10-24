#include "../include/LevelOneBeginState.h"

LevelOneBeginState::LevelOneBeginState(SDL_Renderer *r, int width, int height,
                                       ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    SDL_Color white = {255, 255, 255, 255};
    title = resources->getFont("manaspc80", titleTitle, white);
    ready = resources->getFont("manaspc60", readyTitle, white);
    dialogue = resources->getFont("manaspc60", dialogueTitle, white);
    instructions = resources->getFont("manaspc60", instructionsTitle, white);

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
        switch (e->key.keysym.sym) {
        case SDLK_SPACE:
            return STATE_LEVELONEINSTRUCT;
            break;
        default:
            break;
        }
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

void LevelOneBeginState::startMusic(int vol) { return; }

LevelOneBeginState::~LevelOneBeginState() {
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(ready);
    SDL_DestroyTexture(dialogue);
    SDL_DestroyTexture(instructions);
}
