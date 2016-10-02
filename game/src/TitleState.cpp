#include "../include/TitleState.h"

TitleState::TitleState(SDL_Renderer *r, int width, int height,
                       ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    SDL_Color white = {255, 255, 255, 255};
    titleFont = resources->getFont(std::string("manaspc80"), title, white);

    msgFont = resources->getFont(std::string("manaspc60"), titleMessage, white);

    int textureW;
    int textureH;
    SDL_QueryTexture(msgFont, NULL, NULL, &textureW, &textureH);

    msgRect = {(width - textureW) / 2, (int)floor(height * 0.75), textureW,
               textureH};

    SDL_QueryTexture(titleFont, NULL, NULL, &textureW, &textureH);

    titleRect = {(width - textureW) / 2, (height - textureH) / 2, textureW,
                 textureH};
}

int TitleState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        // TODO: Change to STATE_MAINMENU
        return STATE_GAME;
    }
    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}
void TitleState::doSound() { return; }
void TitleState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return; }
void TitleState::render(int dt) {
    time += dt;
    while (time > 16) {
        time -= 16;
        if (titleAlpha < 255 && !fadein) {
            titleAlpha++;
            fadein = false;
        } else {
            if (titleAlpha > 10) {
                fadein = true;
                titleAlpha = titleAlpha - 5;
            } else {
                fadein = false;
            }
        }
        floatingMove(5, time);
    }

    SDL_SetTextureAlphaMod(titleFont, titleAlpha);

    if (SDL_RenderCopy(renderer, msgFont, NULL, &msgRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, titleFont, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }
}
void TitleState::startMusic() {
    // Add title screen music?
    return;
}

double radToDegs(double r) { return r * M_PI / 180; }

void TitleState::floatingMove(int speed, int dt) {
    if (msgRect.x > 0 - msgRect.w) {
        msgRect.x -= speed;
    } else {
        msgRect.x = width;
    }
    msgRect.y = height * 0.75 + 0.2 * radToDegs(sin(8 * dt));
    return;
}
