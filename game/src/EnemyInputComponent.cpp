#include "../include/EnemyInputComponent.h"
void EnemyInputComponent::update(EnemyObject *enemyObj) {
    int direction = std::rand() % 8;

    switch (direction) {

    case 0:
        //(1,0)
        enemyObj->setXVel(MAX_ACCEL);
        // enemyObj->xVelocity = MAX_ACCEL;
        enemyObj->setYVel(0);
        // enemyObj->yVelocity = 0;
        break;
    case 1:
        //(0,1)
        enemyObj->setXVel(0);
        // enemyObj->xVelocity = 0;
        enemyObj->setYVel(MAX_ACCEL);
        // enemyObj->yVelocity = MAX_ACCEL;
        break;
    case 2:
        //(-1,0)
        enemyObj->setXVel(-MAX_ACCEL);
        // enemyObj->xVelocity = MAX_ACCEL;
        enemyObj->setYVel(0);
        // enemyObj->yVelocity = 0;
        break;
    case 3:
        //(0, -1)
        enemyObj->setXVel(0);
        // enemyObj->xVelocity = 0;
        enemyObj->setYVel(-MAX_ACCEL);
        // enemyObj->yVelocity = -MAX_ACCEL;
        break;
    case 4:
        //(1,1)
        enemyObj->setXVel(MAX_ACCEL);
        // enemyObj->xVelocity = MAX_ACCEL;
        enemyObj->setYVel(MAX_ACCEL);
        // enemyObj->yVelocity = MAX_ACCEL;
        break;
    case 5:
        //(-1,-1)
        enemyObj->setXVel(-MAX_ACCEL);
        // enemyObj->xVelocity = -MAX_ACCEL;
        enemyObj->setYVel(-MAX_ACCEL);
        // enemyObj->yVelocity = -MAX_ACCEL;
        break;
    case 6:
        //(-1,1)
        enemyObj->setXVel(-MAX_ACCEL);
        // enemyObj->xVelocity = -MAX_ACCEL;
        enemyObj->setYVel(MAX_ACCEL);
        // enemyObj->yVelocity = MAX_ACCEL;
        break;
    case 7:
        //(1,-1)
        enemyObj->setXVel(MAX_ACCEL);
        // enemyObj->xVelocity = MAX_ACCEL;
        enemyObj->setYVel(-MAX_ACCEL);
        // enemyObj->yVelocity = -MAX_ACCEL;
        break;
    }
}

EnemyInputComponent::~EnemyInputComponent() {}
