#include "../include/TitleState.h"

TitleState::TitleState(SDL_Renderer *r, int width, int height,
                       ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    titleFont = resources->getFont(std::string("manaspc80"), title);

    msgFont = resources->getFont(std::string("manaspc30"), titleMessage);

    gameTitle = resources->getFont("manaspc80", gameName);

    int textureW;
    int textureH;
    SDL_QueryTexture(msgFont, NULL, NULL, &textureW, &textureH);

    msgRect = {(width - textureW) / 2, (int)floor(height * 0.95), textureW,
               textureH};

    SDL_SetTextureAlphaMod(msgFont, 32);

    SDL_QueryTexture(titleFont, NULL, NULL, &textureW, &textureH);

    titleRect = {(width - textureW) / 2, (int)floor(height * 0.3), textureW,
                 textureH};

    SDL_SetTextureAlphaMod(titleFont, 0);

    SDL_QueryTexture(gameTitle, NULL, NULL, &textureW, &textureH);

    gameTitleRect = {(width - textureW) / 2, (int)floor(height * 0.65),
                     textureW, textureH};
    SDL_SetTextureAlphaMod(gameTitle, 0);
}

int TitleState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        Mix_HaltMusic();
        return STATE_MAINMENU;
    }
    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}
void TitleState::doSound() { return; }
void TitleState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void TitleState::render(int dt) {
    time += dt;
    while (time > 64) {
        time -= 64;
        if (titleAlpha < 255 && !fadein) {
            titleAlpha++;
            fadein = false;
            SDL_SetTextureAlphaMod(titleFont, titleAlpha);
        } else {
            if (titleAlpha > 10) {
                fadein = true;
                titleAlpha = titleAlpha - 5;
            }
        }

        if (fadein) {
            SDL_SetTextureAlphaMod(gameTitle, (255 - titleAlpha));
        }
    }

    if (SDL_RenderCopy(renderer, msgFont, NULL, &msgRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, titleFont, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, gameTitle, NULL, &gameTitleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }
}
void TitleState::startMusic(int vol) {
    Mix_PlayMusic(resources->getMusic("title"), 1);
    Mix_VolumeMusic(vol);
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

TitleState::~TitleState() {
    SDL_DestroyTexture(titleFont);
    SDL_DestroyTexture(msgFont);
    SDL_DestroyTexture(gameTitle);
}
