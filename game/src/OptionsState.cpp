//
//  OptionsState.cpp
//  game
//
//  Created by Tristan Orton-Urbina on 12/11/16.
//  Copyright © 2016 lizard. All rights reserved.
//

#include "OptionsState.h"

OptionsState::OptionsState(SDL_Renderer *r, int width, int height,
                           ResourceManager *res, SDL_Window *window,
                           int *volume) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    myWindow = window;
    masterVol = volume;

    title = resources->getFont("manaspc80", titleTitle);
    audio[0] = resources->getFont("manaspc60", audioTitle);
    bright[0] = resources->getFont("manaspc60", brightnessTitle);
    quitGame[0] = resources->getFont("manaspc60", quitGameTitle);
    navigation = resources->getFont("manaspc20", navigationTitle);

    SDL_Color blue = {43, 238, 248, 255};
    resources->setTextColor(blue);
    audio[1] = resources->getFont("manaspc60", audioTitle);
    bright[1] = resources->getFont("manaspc60", brightnessTitle);
    quitGame[1] = resources->getFont("manaspc60", quitGameTitle);

    SDL_Color white = {255, 255, 255, 255};
    resources->setTextColor(white);

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {(this->width - w) / 2, (int)floor(height * 0.04), w, h};

    SDL_QueryTexture(audio[0], NULL, NULL, &w, &h);
    audioRect = {(this->width - w) / 2, (int)floor(height * 0.20), w, h};

    SDL_QueryTexture(bright[0], NULL, NULL, &w, &h);
    brightRect = {(this->width - w) / 2, (int)floor(height * 0.40), w, h};

    SDL_QueryTexture(quitGame[0], NULL, NULL, &w, &h);
    quitGameRect = {(this->width - w) / 2, (int)floor(height * 0.60), w, h};

    SDL_QueryTexture(navigation, NULL, NULL, &w, &h);
    navigationRect = {(this->width - w) / 2, (int)floor(height * 0.85), w, h};
}

int OptionsState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
        case SDLK_RETURN:
            if (editing == 0) {
                switch (currSelect) {
                case 0: {
                    editing = 1;
                    SDL_DestroyTexture(audio[1]);
                    SDL_Color green = {110, 233, 69, 255};
                    resources->setTextColor(green);
                    audio[1] = resources->getFont("manaspc60", audioTitle);
                    break;
                }
                case 1: {
                    editing = 2;
                    SDL_DestroyTexture(bright[1]);
                    SDL_Color green = {110, 233, 69, 255};
                    resources->setTextColor(green);
                    bright[1] =
                        resources->getFont("manaspc60", brightnessTitle);
                    break;
                }
                case 2:
                    Mix_PlayChannel(-1, resources->getChunk("select"), 0);
                    Mix_HaltMusic();
                    return STATE_MAINMENU;
                }
                SDL_Color white = {255, 255, 255, 255};
                resources->setTextColor(white);
            } else {
                SDL_Color blue = {43, 238, 248, 255};
                resources->setTextColor(blue);
                SDL_DestroyTexture(audio[1]);
                SDL_DestroyTexture(bright[1]);
                audio[1] = resources->getFont("manaspc60", audioTitle);
                bright[1] = resources->getFont("manaspc60", brightnessTitle);
                editing = 0;
                SDL_Color white = {255, 255, 255, 255};
                resources->setTextColor(white);
            }
            break;
        case SDLK_DOWN:
            if (editing == 0) {
                Mix_PlayChannel(-1, resources->getChunk("tick"), 0);
                currSelect++;
                if (currSelect == 3)
                    currSelect = 0;
            }
            break;
        case SDLK_UP:
            if (editing == 0) {
                Mix_PlayChannel(-1, resources->getChunk("tick"), 0);
                currSelect--;
                if (currSelect < 0)
                    currSelect = 2;
            }
            break;
        case SDLK_LEFT:
            if (editing == 1) {
                *masterVol -= 1;
                if (*masterVol < 0)
                    *masterVol = 0;
                else {
                    int w, h;
                    SDL_DestroyTexture(audio[0]);
                    SDL_DestroyTexture(audio[1]);
                    audioTitle = "Volume: " + std::to_string(*masterVol);
                    audio[0] = resources->getFont("manaspc60", audioTitle);
                    SDL_Color green = {110, 233, 69, 255};
                    resources->setTextColor(green);
                    audio[1] = resources->getFont("manaspc60", audioTitle);
                    SDL_QueryTexture(audio[0], NULL, NULL, &w, &h);
                    audioRect = {(this->width - w) / 2,
                                 (int)floor(height * 0.20), w, h};
                    SDL_Color white = {255, 255, 255, 255};
                    resources->setTextColor(white);
                }
                Mix_Volume(-1, *masterVol);
            } else if (editing == 2) {
                currBright -= 1;
                if (currBright < 0)
                    currBright = 0;
                else {
                    int w, h;
                    SDL_DestroyTexture(bright[0]);
                    SDL_DestroyTexture(bright[1]);
                    brightnessTitle =
                        "Brightness: " + std::to_string(currBright);
                    bright[0] =
                        resources->getFont("manaspc60", brightnessTitle);
                    SDL_Color green = {110, 233, 69, 255};
                    resources->setTextColor(green);
                    bright[1] =
                        resources->getFont("manaspc60", brightnessTitle);
                    SDL_QueryTexture(bright[0], NULL, NULL, &w, &h);
                    brightRect = {(this->width - w) / 2,
                                  (int)floor(height * 0.40), w, h};
                    SDL_Color white = {255, 255, 255, 255};
                    resources->setTextColor(white);
                }
                SDL_SetWindowBrightness(myWindow, (float)currBright / 50.0);
            }
            break;
        case SDLK_RIGHT:
            if (editing == 1) {
                *masterVol += 1;
                if (*masterVol > MAX_VOLUME)
                    *masterVol = MAX_VOLUME;
                else {
                    int w, h;
                    SDL_DestroyTexture(audio[0]);
                    SDL_DestroyTexture(audio[1]);
                    audioTitle = "Volume: " + std::to_string(*masterVol);
                    audio[0] = resources->getFont("manaspc60", audioTitle);
                    SDL_Color green = {110, 233, 69, 255};
                    resources->setTextColor(green);
                    audio[1] = resources->getFont("manaspc60", audioTitle);
                    SDL_QueryTexture(audio[0], NULL, NULL, &w, &h);
                    audioRect = {(this->width - w) / 2,
                                 (int)floor(height * 0.20), w, h};
                    SDL_Color white = {255, 255, 255, 255};
                    resources->setTextColor(white);
                }
                Mix_Volume(-1, *masterVol);
            } else if (editing == 2) {
                currBright += 1;
                if (currBright > MAX_BRIGHTNESS)
                    currBright = MAX_BRIGHTNESS;
                else {
                    SDL_DestroyTexture(bright[0]);
                    SDL_DestroyTexture(bright[1]);
                    int w, h;
                    brightnessTitle =
                        "Brightness: " + std::to_string(currBright);
                    bright[0] =
                        resources->getFont("manaspc60", brightnessTitle);
                    SDL_Color green = {110, 233, 69, 255};
                    resources->setTextColor(green);
                    bright[1] =
                        resources->getFont("manaspc60", brightnessTitle);
                    SDL_QueryTexture(bright[0], NULL, NULL, &w, &h);
                    brightRect = {(this->width - w) / 2,
                                  (int)floor(height * 0.40), w, h};
                    SDL_Color white = {255, 255, 255, 255};
                    resources->setTextColor(white);
                }
                SDL_SetWindowBrightness(myWindow, (float)currBright / 50.0);
            }
            break;
        default:
            break;
        }
    }

    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

void OptionsState::doSound() { return; }

void OptionsState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void OptionsState::render(int dt) {

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, audio[0], NULL, &audioRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, bright[0], NULL, &brightRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, quitGame[0], NULL, &quitGameRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, navigation, NULL, &navigationRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    switch (currSelect) {
    case 0:
        if (SDL_RenderCopy(renderer, audio[1], NULL, &audioRect) < 0) {
            std::cout << "Something broke: " << SDL_GetError();
        }
        break;
    case 1:
        if (SDL_RenderCopy(renderer, bright[1], NULL, &brightRect) < 0) {
            std::cout << "Something broke: " << SDL_GetError();
        }
        break;
    case 2:
        if (SDL_RenderCopy(renderer, quitGame[1], NULL, &quitGameRect) < 0) {
            std::cout << "Something broke: " << SDL_GetError();
        }
        break;
    }

    int supressWarning = dt;
    supressWarning++;
}
void OptionsState::startMusic(int vol) {
    Mix_PlayMusic(resources->getMusic("mainMenu"), -1);
    Mix_VolumeMusic(vol);
    return;
}

OptionsState::~OptionsState() {
    SDL_SetWindowBrightness(myWindow, 1.0);
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(audio[0]);
    SDL_DestroyTexture(bright[0]);
    SDL_DestroyTexture(quitGame[0]);
    SDL_DestroyTexture(navigation);

    SDL_DestroyTexture(audio[1]);
    SDL_DestroyTexture(bright[1]);
    SDL_DestroyTexture(quitGame[1]);
}
