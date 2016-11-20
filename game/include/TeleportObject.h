#ifndef TELEPORT_OBJECT_LIZARD
#define TELEPORT_OBJECT_LIZARD

#include "GameObject.h"
#include "PlayerObject.h"
#include "TeleportGraphicsComponent.h"
#include "TeleportPhysicsComponent.h"

class TeleportGraphicsComponent;
class TeleportPhysicsComponent;
class PlayerObject;

class TeleportObject : public GameObject {

public:
    TeleportObject(int x, int y, int newX, int newY, int checkNum,
                   TeleportGraphicsComponent *g, TeleportPhysicsComponent *p,
                   PlayerObject *pl);

    ~TeleportObject();

    float getNewX() { return newXFloat; }
    float getNewY() { return newYFloat; }
    void setNewX(float x) { newXFloat = x; }
    void setNewY(float y) { newYFloat = y; }

    TeleportGraphicsComponent *graphics;
    TeleportPhysicsComponent *physics;
    PlayerObject *playerObj;
    int checkNum;

private:
    float newXFloat, newYFloat;
};

#endif