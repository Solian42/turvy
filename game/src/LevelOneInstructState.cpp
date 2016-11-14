#include "../include/LevelOneInstructState.h"

LevelOneInstructState::LevelOneInstructState(SDL_Renderer *r, int width,
                                             int height, ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    SDL_Color white = {255, 255, 255, 255};
    spikeInfo = resources->getFont("manaspc60", spikeInfoTitle, white);
    checkInfo = resources->getFont("manaspc60", checkInfoTitle, white);
    mechInfo = resources->getFont("manaspc60", mechInfoTitle, white);
    startInfo = resources->getFont("manaspc60", startInfoTitle, white);

    int w, h;
    SDL_QueryTexture(spikeInfo, NULL, NULL, &w, &h);
    spikeInfoRect = {(this->width - w) / 2, (int)floor(height * 0.20), w, h};

    SDL_QueryTexture(checkInfo, NULL, NULL, &w, &h);
    checkInfoRect = {(this->width - w) / 2, (int)floor(height * 0.40), w, h};

    SDL_QueryTexture(mechInfo, NULL, NULL, &w, &h);
    mechInfoRect = {(this->width - w) / 2, (int)floor(height * 0.60), w, h};

    SDL_QueryTexture(startInfo, NULL, NULL, &w, &h);
    startInfoRect = {(this->width - w) / 2, (int)floor(height * 0.80), w, h};
}

int LevelOneInstructState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
        case SDLK_SPACE:
            return STATE_GAME;
            break;
        default:
            break;
        }
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

    if (SDL_RenderCopy(renderer, spikeInfo, NULL, &spikeInfoRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, checkInfo, NULL, &checkInfoRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, mechInfo, NULL, &mechInfoRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, startInfo, NULL, &startInfoRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    int supressWarning = dt;
    supressWarning++;
}

void LevelOneInstructState::startMusic(int vol) {
    int t = vol;
    t++;
    return;
}

LevelOneInstructState::~LevelOneInstructState() {
    SDL_DestroyTexture(spikeInfo);
    SDL_DestroyTexture(checkInfo);
    SDL_DestroyTexture(mechInfo);
    SDL_DestroyTexture(startInfo);
}
