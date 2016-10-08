#include "../include/HighScoreState.h"

HighScoreState::HighScoreState(SDL_Renderer *r, int width, int height,
                               ResourceManager *res) {

    this->width = width;
    this->height = height;
    resources = res;
    renderer = r;
    SDL_Color white = {255, 255, 255, 255};
    title = resources->getFont("manaspc60", titleTitle, white);
    highScore = resources->getFont("manaspc60", highScoreTitle, white);
    backToMenu = resources->getFont("manaspc60", backToMenuTitle, white);

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {(this->width - w) / 2, (int)floor(height * 0.16), w, h};

    SDL_QueryTexture(highScore, NULL, NULL, &w, &h);
    highScoreRect = {(this->width - w) / 2, (int)floor(height * 0.32), w, h};

    SDL_QueryTexture(backToMenu, NULL, NULL, &w, &h);
    backToMenuRect = {(this->width - w) / 2, (int)floor(height * 0.48), w, h};
}

int HighScoreState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
        case SDLK_SPACE:
            return STATE_MAINMENU;
            break;
        default:
            break;
        }
    }
    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

std::string HighScoreState::getHighScore() {
    std::ifstream inputFile;
    inputFile.open("../data/text/highscore.txt");
    std::string data;

    inputFile >> data;

    inputFile.close();
    return data;
}

void HighScoreState::doSound() { return; }

void HighScoreState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void HighScoreState::render(int dt) {

    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, backToMenu, NULL, &backToMenuRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, highScore, NULL, &highScoreRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }
    int supressWarning = dt;
    supressWarning++;
}
void HighScoreState::startMusic() {
    // Add menu screen music?
    return;
}

HighScoreState::~HighScoreState() {
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(highScore);
    SDL_DestroyTexture(backToMenu);
}
