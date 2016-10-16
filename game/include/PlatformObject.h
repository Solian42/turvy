#ifndef PLATFORM_OBJECT_LIZARD
#define PLATFORM_OBJECT_LIZARD

#include "GameObject.h"
#include "TerrainObject.h"

class TerrainGraphicsComponent;

class PlatformObject : public TerrainObject {

public:
    PlatformObject(int x, int y, int w, int h, TerrainGraphicsComponent *g);

    TerrainGraphicsComponent *graphics;
};

#endif