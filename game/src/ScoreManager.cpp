#include "../include/ScoreManager.h"

ScoreManager::ScoreManager(SDL_Renderer *r, ResourceManager *res,
                           World *world) {
    renderer = r;
    resources = res;
    this->world = world;
}

int ScoreManager::getScore() { return 100000 - (500) * numDeaths; }
void ScoreManager::update() {
    if (world->collision) {
        numDeaths++;
    }
}
void ScoreManager::resetScore() { numDeaths = 0; }
void ScoreManager::printScore(int width, int height) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Texture *scoreTexture = resources->getFont(
        std::string("manaspc30"),
        std::string("Current Score = ") + std::to_string(getScore()), white);
    int w, h;
    SDL_QueryTexture(scoreTexture, NULL, NULL, &w, &h);
    SDL_Rect temp = {(width - w) / 2, height, w, h};
    SDL_RenderCopy(renderer, scoreTexture, NULL, &temp);
    SDL_DestroyTexture(scoreTexture);
}

ScoreManager::~ScoreManager() {}
