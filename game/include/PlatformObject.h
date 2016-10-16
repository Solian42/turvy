#ifndef PLATFORM_OBJECT_LIZARD
#define PLATFORM_OBJECT_LIZARD

#include "GameObject.h"
#include "PlatformGraphicsComponent.h"

class PlatformGraphicsComponent;

class PlatformObject : public GameObject {

public:
    PlatformObject(int x, int y, int w, int h, PlatformGraphicsComponent *g);

    PlatformGraphicsComponent *graphics;
};

#endif