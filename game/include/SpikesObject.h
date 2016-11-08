#ifndef SPIKES_OBJECT_LIZARD
#define SPIKES_OBJECT_LIZARD

#include "GameObject.h"
#include "SpikesGraphicsComponent.h"

class SpikesGraphicsComponent;

class SpikesObject : public GameObject {

public:
    SpikesObject(int x, int y, int orientation, int spikeNum,
                 SpikesGraphicsComponent *g);
    int getOrientation() { return orientation; }
    void setOrientation(int o) { orientation = o; }

    ~SpikesObject();

    SpikesGraphicsComponent *graphics;
    int spikeNum;

private:
    int orientation = 0;
};

#endif
