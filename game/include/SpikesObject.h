#ifndef PLATFORM_OBJECT_LIZARD
#define PLATFORM_OBJECT_LIZARD

#include "GameObject.h"
#include "TerrainObject.h"

class TerrainGraphicsComponent;

class SpikesObject : public TerrainObject {

public:
    SpikesObject(int x, int y, int w, int h, TerrainGraphicsComponent *g);

    TerrainGraphicsComponent *graphics;
};

#endif