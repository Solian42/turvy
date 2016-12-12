#include "../include/MainMenuState.h"

MainMenuState::MainMenuState(SDL_Renderer *r, int width, int height,
                             ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;

    title[0] = resources->getFont("manaspc80", titleTitle);
    newGame[0] = resources->getFont("manaspc60", newGameTitle);
    highScore[0] = resources->getFont("manaspc60", highScoreTitle);
    quitGame[0] = resources->getFont("manaspc60", quitGameTitle);
    adjustBright[0] = resources->getFont("manaspc60", adjustBrightTitle);
    navigation = resources->getFont("manaspc30", navigationTitle);

    SDL_Color blue = {43, 238, 248, 255};
    resources->setTextColor(blue);
    title[1] = resources->getFont("manaspc80", titleTitle);
    newGame[1] = resources->getFont("manaspc60", newGameTitle);
    highScore[1] = resources->getFont("manaspc60", highScoreTitle);
    quitGame[1] = resources->getFont("manaspc60", quitGameTitle);
    adjustBright[1] = resources->getFont("manaspc60", adjustBrightTitle);

    SDL_Color white = {255, 255, 255, 255};
    resources->setTextColor(white);

    int w, h;
    SDL_QueryTexture(title[0], NULL, NULL, &w, &h);
    titleRect = {(this->width - w) / 2, (int)floor(height * 0.04), w, h};

    SDL_QueryTexture(newGame[0], NULL, NULL, &w, &h);
    newGameRect = {(this->width - w) / 2, (int)floor(height * 0.20), w, h};

    SDL_QueryTexture(highScore[0], NULL, NULL, &w, &h);
    highScoreRect = {(this->width - w) / 2, (int)floor(height * 0.36), w, h};

    SDL_QueryTexture(quitGame[0], NULL, NULL, &w, &h);
    quitGameRect = {(this->width - w) / 2, (int)floor(height * 0.52), w, h};

    SDL_QueryTexture(adjustBright[0], NULL, NULL, &w, &h);
    adjustBrightRect = {(this->width - w) / 2, (int)floor(height * 0.68), w, h};

    SDL_QueryTexture(navigation, NULL, NULL, &w, &h);
    navigationRect = {(this->width - w) / 2, (int)floor(height * 0.85), w, h};
}

int MainMenuState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
        case SDLK_RETURN:
            Mix_PlayChannel(-1, resources->getChunk("select"), 0);

            switch (currSelect) {
            case 0:
                Mix_HaltMusic();
                return STATE_LEVELONEBEGIN;
                break;
            case 1:
                Mix_HaltMusic();
                return STATE_HIGHSCORE;
            case 2:
                Mix_HaltMusic();
                SDL_Event user_event;
                user_event.type = SDL_KEYUP;
                user_event.key.keysym.sym = SDLK_ESCAPE;
                user_event.key.repeat = 0;
                SDL_PushEvent(&user_event);
                return STATE_MAINMENU;
            case 3:
                return STATE_OPTIONS;
            }
            Mix_HaltMusic();
            return STATE_LEVELONEBEGIN;
            break;
        case SDLK_h:
            Mix_HaltMusic();
            return STATE_HIGHSCORE;
        case SDLK_l:
            return STATE_LEVELEDITOR;
        case SDLK_DOWN:
            Mix_PlayChannel(-1, resources->getChunk("tick"), 0);
            currSelect++;
            if (currSelect == 4)
                currSelect = 0;
            break;
        case SDLK_UP:
            Mix_PlayChannel(-1, resources->getChunk("tick"), 0);
            currSelect--;
            if (currSelect < 0)
                currSelect = 3;
            break;
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

    if (SDL_RenderCopy(renderer, title[0], NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, newGame[0], NULL, &newGameRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, highScore[0], NULL, &highScoreRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, quitGame[0], NULL, &quitGameRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, adjustBright[0], NULL, &adjustBrightRect) <
        0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, navigation, NULL, &navigationRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    switch (currSelect) {
    case 0:
        if (SDL_RenderCopy(renderer, newGame[1], NULL, &newGameRect) < 0) {
            std::cout << "Something broke: " << SDL_GetError();
        }
        break;
    case 1:
        if (SDL_RenderCopy(renderer, highScore[1], NULL, &highScoreRect) < 0) {
            std::cout << "Something broke: " << SDL_GetError();
        }
        break;
    case 2:
        if (SDL_RenderCopy(renderer, quitGame[1], NULL, &quitGameRect) < 0) {
            std::cout << "Something broke: " << SDL_GetError();
        }
        break;
    case 3:
        if (SDL_RenderCopy(renderer, adjustBright[1], NULL, &adjustBrightRect) <
            0) {
            std::cout << "Something broke: " << SDL_GetError();
        }
        break;
    }

    int supressWarning = dt;
    supressWarning++;
}
void MainMenuState::startMusic(int vol) {
    Mix_VolumeMusic(vol);
    Mix_PlayMusic(resources->getMusic("mainMenu"), -1);
    Mix_VolumeMusic(vol);
    return;
}

MainMenuState::~MainMenuState() {
    SDL_DestroyTexture(title[0]);
    SDL_DestroyTexture(newGame[0]);
    SDL_DestroyTexture(highScore[0]);
    SDL_DestroyTexture(quitGame[0]);
    SDL_DestroyTexture(adjustBright[0]);

    SDL_DestroyTexture(title[1]);
    SDL_DestroyTexture(newGame[1]);
    SDL_DestroyTexture(highScore[1]);
    SDL_DestroyTexture(quitGame[1]);
    SDL_DestroyTexture(adjustBright[1]);
}
