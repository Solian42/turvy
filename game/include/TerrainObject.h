#ifndef TERRAIN_OBJECT_LIZARD
#define TERRAIN_OBJECT_LIZARD

#include "GameObject.h"
#include "TerrainGraphicsComponent."

class TerrainObject : public GameObject {

public:

    bool isSpikes() { return spikes; }
    bool isUpsideDown() { return upsideDown; }
    void setSpikes(bool s) { spikes = s; }
    void setOrientation(bool o) { upsideDown = o; }

private:
	bool spikes = false;
	bool upsideDown = false;
};

#endif