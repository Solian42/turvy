#ifndef PLATFORM_OBJECT_LIZARD
#define PLATFORM_OBJECT_LIZARD

#include "GameObject.h"
#include "SpikesGraphicsComponent.h"

class SpikesGraphicsComponent;

class SpikesObject : public GameObject {

public:
    SpikesObject(int x, int y, bool orientation, SpikesGraphicsComponent *g);
    bool isUpsideDown() { return upsideDown; }
    void setOrientation(bool o) { upsideDown = o; }
    
    SpikesGraphicsComponent *graphics;

private:
	bool upsideDown = false;
};

#endif