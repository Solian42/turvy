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
    int x, y, xVelocity, yVelocity;
    EnemyObject(int x, int y, int xVelocity, int yVelocity,
                EnemyInputComponent *i, EnemyGraphicsComponent *g,
                EnemyPhysicsComponent *p, int entityNum);
    ~EnemyObject();

    int enemySpriteW, enemySpriteH;
    int entityNum;

    EnemyInputComponent *input;
    EnemyGraphicsComponent *graphics;
    EnemyPhysicsComponent *physics;

  private:
};

#endif
