#ifndef ENEMY_OBJECT_LIZARD
#define ENEMY_OBJECT_LIZARD

#include "EnemyGraphicsComponent.h"
#include "EnemyInputComponent.h"
#include "EnemyPhysicsComponent.h"
#include "GameObject.h"

class EnemyInputComponent;
class EnemyGraphicsComponent;
class EnemyPhysicsComponent;

class EnemyObject : public GameObject {

public:
    EnemyObject(int x, int y, int direction, EnemyInputComponent *i,
                EnemyGraphicsComponent *g, EnemyPhysicsComponent *p,
                int entityNum);
    ~EnemyObject();
    EnemyInputComponent *input;
    EnemyGraphicsComponent *graphics;
    EnemyPhysicsComponent *physics;
    bool direction = 0;

private:
};

#endif
