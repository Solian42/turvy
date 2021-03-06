#ifndef CHECKPOINT_OBJECT_LIZARD
#define CHECKPOINT_OBJECT_LIZARD

#include "CheckpointGraphicsComponent.h"
#include "GameObject.h"

class CheckpointGraphicsComponent;

class CheckpointObject : public GameObject {

public:
    CheckpointObject(int x, int y, int checkNum,
                     CheckpointGraphicsComponent *g);

    ~CheckpointObject();

    CheckpointGraphicsComponent *graphics;
    int checkNum;

private:
};

#endif