#include "../include/ScoreManager.h"

ScoreManager::ScoreManager(SDL_Renderer *r, ResourceManager *res, World *world,
                           int deaths, int coins) {
    renderer = r;
    resources = res;
    numDeaths = deaths;
    numCoins = coins;
    this->world = world;
}

int ScoreManager::getScore() {
    return 100000 - (500) * numDeaths + (2000) * numCoins;
}
void ScoreManager::update() {
    if ((world->isCollidingWithSpike() || world->isCollidingWithEnemy()) &&
        !hasDied) {
        numDeaths++;
        hasDied = true;
    }
    if (world->isCollidingWithCoin()) {
        numCoins++;
        world->setCoinCollision(false);
    }
}
void ScoreManager::resetScore() {
    numDeaths = 0;
    numCoins = 0;
}
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

void ScoreManager::setCoins(int coins) { numCoins = coins; }

void ScoreManager::setDeaths(int deaths) { numDeaths = deaths; }

int ScoreManager::getCoins() { return numCoins; }

int ScoreManager::getDeaths() { return numDeaths; }

ScoreManager::~ScoreManager() {}
