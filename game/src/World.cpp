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

World::World(int numEntities) {
    entityVolumes = std::vector<SDL_Rect>(numEntities);
    this->numEntities = numEntities;
}

SDL_Rect World::getEntityLocation(int num) { return entityVolumes[num]; }

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
    for (SDL_Rect o : platformVolumes) {
        SDL_Rect pRect = *obj->getLocation();
        SDL_bool result = SDL_IntersectRect(&o, obj->getLocation(), &intersect);
        if (result == SDL_TRUE) {

            int hd =
                abs((((pRect.x + pRect.w) / 2) * ((pRect.x + pRect.w) / 2)) +
                    (((o.x + o.w) / 2) * ((o.x + o.w) / 2)));
            int vd =
                abs((((pRect.y + pRect.h) / 2) * ((pRect.y + pRect.h) / 2)) +
                    (((o.y + o.h) / 2) * ((o.y + o.h) / 2)));

            if (hd < vd) {
                if (((pRect.x + pRect.w) / 2) < ((o.x + o.w) / 2)) {
                    // Collision on right side of player
                    return COLLIDE_RIGHT;
                } else {
                    // Collision on left side of player
                    return COLLIDE_LEFT;
                }
            } else if (vd < hd) {

                if (((pRect.y + pRect.h) / 2) < ((o.y + o.h) / 2)) {
                    // Collision on bottom side of player
                    return COLLIDE_DOWN;
                } else {
                    // Collision on top side of player
                    return COLLIDE_UP;
                }
            }
        }
    }
    return NO_COLLIDE;
}
