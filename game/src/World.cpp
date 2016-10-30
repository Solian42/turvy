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

World::World(int numEntities, int numPlatforms, int numSpikes,
             int numCheckpoints) {
    entityVolumes = std::vector<SDL_Rect>(numEntities);
    platformVolumes = std::vector<SDL_Rect>(numPlatforms);
    spikeVolumes = std::vector<SDL_Rect>(numSpikes);
    checkpointVolumes = std::vector<SDL_Rect>(numCheckpoints);
    this->numPlatforms = numPlatforms;
    this->numSpikes = numSpikes;
    this->numEntities = numEntities;
    this->numCheckpoints = numCheckpoints;
}

SDL_Rect World::getEntityLocation(int num) { return entityVolumes[num]; }
SDL_Rect World::getPlatformLocation(int num) { return platformVolumes[num]; }
SDL_Rect World::getSpikeLocation(int num) { return spikeVolumes[num]; }
SDL_Rect World::getCheckpointLocation(int num) {
    return checkpointVolumes[num];
}

int World::transformXtoCamera(int x) { return x - cameraX; }

int World::transformYtoCamera(int y) {
    return (this->worldYLen - (y - cameraY));
}

void World::updateVolume(int entityNum, int newX, int newY, int newW,
                         int newH) {
    entityVolumes[entityNum].x = newX;
    entityVolumes[entityNum].y = newY;
    entityVolumes[entityNum].w = newW;
    entityVolumes[entityNum].h = newH;
}

bool World::checkCollisions() {
    bool collision = false;
    for (int i = 1; i < numEntities; i++) {
        collision =
            collision || testCollide(entityVolumes[0], entityVolumes[i]);
    }
    return collision;
}

int World::collideWithPlatform(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    int returnResult = 0;
    for (SDL_Rect o : platformVolumes) {
        SDL_Rect pRect = *obj->getLocation();
        SDL_bool result = SDL_IntersectRect(&o, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
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
    }
    return returnResult;
}

bool World::collideWithSpike(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    for (SDL_Rect s : spikeVolumes) {
        SDL_bool result = SDL_IntersectRect(&s, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
            collision = true;
            return true;
        }
    }
    collision = false;
    return false;
}

bool World::collideWithCheckpoint(GameObject *obj) {
    SDL_Rect intersect = {0, 0, 0, 0};
    for (SDL_Rect c : checkpointVolumes) {
        SDL_bool result = SDL_IntersectRect(&c, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {
            setCurrCheckX(c.x);
            setCurrCheckY(c.y);
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
