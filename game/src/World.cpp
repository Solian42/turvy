#include "../include/World.h"

bool World::testCollide(SDL_Rect a, SDL_Rect b) {
    SDL_Rect intersect = {0, 0, 0, 0};
    SDL_Rect aTransform = {a.x, a.y, a.w, a.h};
    SDL_Rect bTransform = {b.x, b.y, b.w, b.h};
    SDL_bool result = SDL_IntersectRect(&aTransform, &bTransform, &intersect);
    if (result == SDL_TRUE) {
        return true;
    }
    return false;
}

World::World(int width, int height, int numEntities, int numPlatforms,
             int numSpikes, int numCheckpoints, int numCoins,
             int numTrampolines, int numEnemies, int numTeleports,
             int numDialogues) {
    worldXLen = width;
    worldYLen = height;
    entityVolumes = std::vector<SDL_Rect>(numEntities);
    platformVolumes = std::vector<SDL_Rect>(numPlatforms);
    spikeVolumes = std::vector<SDL_Rect>(numSpikes);
    checkpointVolumes = std::vector<SDL_Rect>(numCheckpoints);
    coinVolumes = std::vector<SDL_Rect>(numCoins);
    trampolineVolumes = std::vector<SDL_Rect>(numTrampolines);
    enemyVolumes = std::vector<SDL_Rect>(numEnemies);
    teleportVolumes = std::vector<SDL_Rect>(numTeleports);
    dialogueVolumes = std::vector<SDL_Rect>(numDialogues);
    this->numPlatforms = numPlatforms;
    this->numSpikes = numSpikes;
    this->numEntities = numEntities;
    this->numCheckpoints = numCheckpoints;
    this->numCoins = numCoins;
    this->numTrampolines = numTrampolines;
    this->numEnemies = numEnemies;
    this->numTeleports = numTeleports;
    this->numDialogues = numDialogues;
}

SDL_Rect World::getEntityLocation(int num) { return entityVolumes[num]; }
SDL_Rect World::getPlatformLocation(int num) { return platformVolumes[num]; }
SDL_Rect World::getSpikeLocation(int num) { return spikeVolumes[num]; }
SDL_Rect World::getCheckpointLocation(int num) {
    return checkpointVolumes[num];
}
SDL_Rect World::getCoinLocation(int num) { return coinVolumes[num]; }
SDL_Rect World::getTrampolineLocation(int num) {
    return trampolineVolumes[num];
}
SDL_Rect World::getEnemyLocation(int num) { return enemyVolumes[num]; }
SDL_Rect World::getTeleportLocation(int num) { return teleportVolumes[num]; }
SDL_Rect World::getDialogueLocation(int num) { return dialogueVolumes[num]; }

int World::transformXtoCamera(int x) { return x - cameraX; }

int World::transformYtoCamera(int y) { return camera.h - (y - cameraY); }

void World::setCameraH(int h) { camera.h = h; }

int World::transformXToWorld(int x) { return x; }

int World::transformYToWorld(int y) { return worldYLen - y; }

void World::updateVolume(int entityNum, int newX, int newY, int newW,
                         int newH) {
    entityVolumes[entityNum].x = newX;
    entityVolumes[entityNum].y = newY;
    entityVolumes[entityNum].w = newW;
    entityVolumes[entityNum].h = newH;
}

bool World::checkSpikeCollisions() {
    bool spikeCollision = false;
    for (int i = 0; i < numSpikes; i++) {
        spikeCollision =
            spikeCollision || testCollide(entityVolumes[0], spikeVolumes[i]);
    }
    return spikeCollision && !godMode;
}

bool World::checkEnemyCollisions() {
    bool enemyCollision = false;
    for (int i = 0; i < numEnemies; i++) {
        enemyCollision =
            enemyCollision || testCollide(entityVolumes[0], enemyVolumes[i]);
    }
    return enemyCollision && !godMode;
}

bool World::checkTeleportCollisions() {
    bool teleportCollision = false;
    for (int i = 0; i < numTeleports; i++) {
        teleportCollision = teleportCollision ||
                            testCollide(entityVolumes[0], teleportVolumes[i]);
    }
    return teleportCollision;
}

platCollisionInfo World::collideWithPlatform(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    SDL_Rect tempintersect = {0, 0, 0, 0};
    int returnResult = NO_COLLIDE;
    for (SDL_Rect o : platformVolumes) {
        SDL_Rect pRect = *obj->getLocation();
        SDL_bool result = SDL_IntersectRect(&o, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
            if(intersect.w == intersect.h){
                if(intersect.x == o.x && intersect.y == o.y){
                    returnResult |= COLLIDE_DL;
                } else if(intersect.x == o.x && intersect.y != o.y){
                    returnResult |= COLLIDE_UL;
                } else if(intersect.x != o.x && intersect.y == o.y){
                    returnResult |= COLLIDE_DR;
                } else {
                    returnResult |= COLLIDE_UR;
                }
            } else {

                if (pRect.x < o.x + o.w && pRect.x + pRect.w > o.x &&
                    pRect.y + pRect.h < o.y && intersect.w >= intersect.h) {
                    returnResult |= COLLIDE_UP;
                } else if (pRect.x < o.x + o.w && pRect.x + pRect.w > o.x &&
                           pRect.y < o.y + o.h && intersect.w > intersect.h) {
                    returnResult |= COLLIDE_DOWN;
                } else if (pRect.x < o.x + o.w && pRect.x > o.x &&
                           pRect.y + pRect.h > o.y && pRect.y < o.y + o.h &&
                           intersect.w <= intersect.h) {
                    returnResult |= COLLIDE_LEFT;
                } else if (pRect.x + pRect.w > o.x && pRect.x < o.x + o.w &&
                           pRect.y + pRect.h > o.y && pRect.y < o.y + o.h &&
                           intersect.w < intersect.h) {
                    returnResult |= COLLIDE_RIGHT;
                }
            }
            tempintersect = intersect;
        }
    }
    return platCollisionInfo{returnResult, tempintersect};
}

bool World::collideWithSpike(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    for (SDL_Rect s : spikeVolumes) {
        SDL_bool result = SDL_IntersectRect(&s, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
            spikeCollision = true;
            return true && !godMode;
        }
    }
    spikeCollision = false;
    return false;
}

bool World::collideWithEnemies(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    for (SDL_Rect e : enemyVolumes) {
        SDL_bool result = SDL_IntersectRect(&e, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
            enemyCollision = true;
            return true && !godMode;
        }
    }
    enemyCollision = false;
    return false;
}

bool World::collideWithCheckpoint(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    for (SDL_Rect c : checkpointVolumes) {
        SDL_bool result = SDL_IntersectRect(&c, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
            setCurrCheckX(c.x);
            setCurrCheckY(c.y);
            checkpointCollision = true;
            return true;
        }
    }
    checkpointCollision = false;
    return false;
}

std::pair<bool, SDL_Rect> World::collideWithTeleport(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    for (SDL_Rect te : teleportVolumes) {
        SDL_bool result =
            SDL_IntersectRect(&te, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
            teleportCollision = true;
            return std::make_pair(true, intersect);
        }
    }
    teleportCollision = false;
    return std::make_pair(false, intersect);
}

std::pair<bool, SDL_Rect> World::collideWithCoin(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    for (SDL_Rect co : coinVolumes) {
        SDL_bool result =
            SDL_IntersectRect(&co, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
            return std::make_pair(true, intersect);
        }
    }
    return std::make_pair(false, intersect);
}

bool World::collideWithTrampoline(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    for (SDL_Rect t : trampolineVolumes) {
        SDL_bool result = SDL_IntersectRect(&t, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
            return true;
        }
    }
    return false;
}

bool World::intersectCamera(SDL_Rect *toTest) {
    SDL_bool result = SDL_TRUE;
    SDL_Rect intersect = {0, 0, 0, 0};
    result = SDL_IntersectRect(toTest, &camera, &intersect);
    if (result == SDL_TRUE) {
        return true;
    }
    return false;
}
