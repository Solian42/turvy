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
    currScore =
        resources->getFont("manaspc60", std::to_string(currScoreInt), white);
    currTitle = resources->getFont("manaspc60", currTitleTitle, white);

    int w, h;
    SDL_QueryTexture(title, NULL, NULL, &w, &h);
    titleRect = {(this->width - w) / 2, (int)floor(height * 0.16), w, h};

    SDL_QueryTexture(highScore, NULL, NULL, &w, &h);
    highScoreRect = {(this->width - w) / 2, (int)floor(height * 0.26), w, h};

    SDL_QueryTexture(backToMenu, NULL, NULL, &w, &h);
    backToMenuRect = {(this->width - w) / 2, (int)floor(height * 0.80), w, h};

    SDL_QueryTexture(currScore, NULL, NULL, &w, &h);
    currScoreRect = {(this->width - w) / 2, (int)floor(height * 0.60), w, h};

    SDL_QueryTexture(currTitle, NULL, NULL, &w, &h);
    currTitleRect = {(this->width - w) / 2, (int)floor(height * 0.48), w, h};
}

int HighScoreState::handleEvent(SDL_Event *e, int dt) {
    if (e->type == SDL_KEYUP) {
        switch (e->key.keysym.sym) {
        case SDLK_SPACE:
            Mix_HaltMusic();
            return STATE_MAINMENU;
            break;
        case SDLK_r:
            setHighScore(0);
            break;
        default:
            break;
        }
    }
    int supressWarning = dt;
    supressWarning++;
    return getMyState();
}

void HighScoreState::setCurrScore(int score) {
    currScoreInt = score;
    SDL_Color white = {255, 255, 255, 255};
    SDL_DestroyTexture(currScore);
    if (currScoreInt == -1) {
        currScore =
            resources->getFont("manaspc60", "No score found. :(", white);
    } else {
        currScore = resources->getFont("manaspc60",
                                       std::to_string(currScoreInt), white);
        if (std::stoi(getHighScore()) < currScoreInt) {
            setHighScore(currScoreInt);
        }
    }

    int w, h;
    SDL_QueryTexture(currScore, NULL, NULL, &w, &h);
    currScoreRect = {(this->width - w) / 2, (int)floor(height * 0.60), w, h};
}

std::string HighScoreState::getHighScore() {
    std::ifstream inputFile;
    inputFile.open("../data/text/highscore.txt");
    std::string data;

    if (!(inputFile >> data))
        data = std::to_string(0);

    inputFile.close();
    if (std::stoi(data) == -1) {
        highScoreTitle = "No current high score.. :(";
    } else {
        highScoreTitle = data;
    }

    SDL_DestroyTexture(highScore);
    SDL_Color white = {255, 255, 255, 255};
    highScore = resources->getFont("manaspc60", highScoreTitle, white);
    int w, h;
    SDL_QueryTexture(highScore, NULL, NULL, &w, &h);
    highScoreRect = {(this->width - w) / 2, (int)floor(height * 0.32), w, h};
    return data;
}

void HighScoreState::setHighScore(int score) {
    std::ofstream outFile;
    outFile.open("../data/text/highscore.txt");
    outFile << score;
    outFile.close();
}

void HighScoreState::doSound() { return; }

void HighScoreState::doPhysics(int dt) {
    int supressWarning = dt;
    supressWarning++;
    return;
}
void HighScoreState::render(int dt) {
    getHighScore();
    if (SDL_RenderCopy(renderer, title, NULL, &titleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, backToMenu, NULL, &backToMenuRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, highScore, NULL, &highScoreRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, currScore, NULL, &currScoreRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    if (SDL_RenderCopy(renderer, currTitle, NULL, &currTitleRect) < 0) {
        std::cout << "Something broke: " << SDL_GetError();
    }

    int supressWarning = dt;
    supressWarning++;
}
void HighScoreState::startMusic(int vol) {
    Mix_PlayMusic(resources->getMusic("highscore"), -1);
    Mix_VolumeMusic(vol);
    return;
}

HighScoreState::~HighScoreState() {
    SDL_DestroyTexture(title);
    SDL_DestroyTexture(highScore);
    SDL_DestroyTexture(backToMenu);
    SDL_DestroyTexture(currScore);
    SDL_DestroyTexture(currTitle);
}
