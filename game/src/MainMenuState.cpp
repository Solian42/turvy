#include "../include/MainMenuState.h"

MainMenuState::MainMenuState(SDL_Renderer *r, int width, int height,
                             ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    SDL_Color white = {255, 255, 255, 255};
    title = resources->getFont("manaspc80", titleTitle, white);
    newGame = resources->getFont("manaspc60", newGameTitle, white);
    highScore = resources->getFont("manaspc60", highScoreTitle, white);
    quitGame = resources->getFont("manaspc60", quitGameTitle, white);
    adjustBright = resources->getFont("manaspc60", adjustBrightTitle, white);
    adjustVol = resources->getFont("manaspc60", adjustVolTitle, white);

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {(this->width - w) / 2, (int)floor(height * 0.04), w, h};

    SDL_QueryTexture(newGame, NULL, NULL, &w, &h);
    newGameRect = {(this->width - w) / 2, (int)floor(height * 0.20), w, h};

    SDL_QueryTexture(highScore, NULL, NULL, &w, &h);
    highScoreRect = {(this->width - w) / 2, (int)floor(height * 0.36), w, h};

    SDL_QueryTexture(quitGame, NULL, NULL, &w, &h);
    quitGameRect = {(this->width - w) / 2, (int)floor(height * 0.52), w, h};

    SDL_QueryTexture(adjustBright, NULL, NULL, &w, &h);
    adjustBrightRect = {(this->width - w) / 2, (int)floor(height * 0.68), w, h};

    SDL_QueryTexture(adjustVol, NULL, NULL, &w, &h);
    adjustVolRect = {(this->width - w) / 2, (int)floor(height * 0.84), w, h};
}

int MainMenuState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
        case SDLK_SPACE:
            Mix_HaltMusic();
            return STATE_GAME;
            break;
        case SDLK_h:
            Mix_HaltMusic();
            return STATE_HIGHSCORE;
        default:
            break;
        }
    }

    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

void MainMenuState::doSound() { return; }

void MainMenuState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void MainMenuState::render(int dt) {

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, newGame, NULL, &newGameRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, highScore, NULL, &highScoreRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, quitGame, NULL, &quitGameRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, adjustBright, NULL, &adjustBrightRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, adjustVol, NULL, &adjustVolRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }
    int supressWarning = dt;
    supressWarning++;
}
void MainMenuState::startMusic(int vol) {
    Mix_PlayMusic(resources->getMusic("mainMenu"), -1);
    Mix_VolumeMusic(vol);
    return;
}

MainMenuState::~MainMenuState() {
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(newGame);
    SDL_DestroyTexture(highScore);
    SDL_DestroyTexture(quitGame);
    SDL_DestroyTexture(adjustBright);
    SDL_DestroyTexture(adjustVol);
}
