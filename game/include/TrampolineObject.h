#ifndef TRAMPOLINE_OBJECT_LIZARD
#define TRAMPOLINE_OBJECT_LIZARD

#include "GameObject.h"
#include "TrampolineGraphicsComponent.h"

class TrampolineGraphicsComponent;

class TrampolineObject : public GameObject {

public:
    TrampolineObject(int x, int y, int trampolineNum,
                 TrampolineGraphicsComponent *g);

    ~TrampolineObject();

    TrampolineGraphicsComponent *graphics;
    int trampolineNum;

private:
};

#endif