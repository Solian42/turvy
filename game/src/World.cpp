#include "../include/World.h"

bool World::testCollide(SDL_Rect a, SDL_Rect b) {
    SDL_Rect intersect = {0, 0, 0, 0};
    SDL_Rect aTransform = {transformX(a.x), transformY(a.y), a.w, a.h};
    SDL_Rect bTransform = {transformX(b.x), transformY(b.y), b.w, b.h};
    SDL_bool result = SDL_IntersectRect(&aTransform, &bTransform, &intersect);
    if (result == SDL_TRUE) {
        return true;
    }
    return false;
}

World::World(int numEntities) {
    entityVolumes = std::vector<SDL_Rect>(numEntities);
    this->numEntities = numEntities;
}

SDL_Rect World::getEntityLocation(int num) { return entityVolumes[num]; }

int World::transformX(int x) { return x; }

int World::transformY(int y) { return (this->y - y); }

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
