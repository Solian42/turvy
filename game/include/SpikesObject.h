#ifndef SPIKES_OBJECT_LIZARD
#define SPIKES_OBJECT_LIZARD

#include "GameObject.h"
#include "SpikesGraphicsComponent.h"

class SpikesGraphicsComponent;

class SpikesObject : public GameObject {

public:
    SpikesObject(int x, int y, bool orientation, int spikeNum,
                 SpikesGraphicsComponent *g);
    bool isUpsideDown() { return upsideDown; }
    void setOrientation(bool o) { upsideDown = o; }

    ~SpikesObject();

    SpikesGraphicsComponent *graphics;
    int spikeNum;

private:
    bool upsideDown = false;
};

#endif
