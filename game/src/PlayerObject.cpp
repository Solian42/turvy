#include "../include/PlayerObject.h"

PlayerObject::PlayerObject(int x, int y, float xVelocity, float yVelocity,
                           PlayerInputComponent *i, PlayerGraphicsComponent *g,
                           PlayerSoundComponent *s, PlayerPhysicsComponent *p,
                           int entityNum) {
    location = {x, y, 0, 0};
    this->xFloat = (float)x;
    this->yFloat = (float)y;
    this->xVelocity = xVelocity;
    this->yVelocity = yVelocity;
    this->input = i;
    this->graphics = g;
    this->sound = s;
    this->physics = p;
    g->setGameObject(this);
    s->setGameObject(this);
    this->location = (g->getTextureRect(g->getCurrentSprite()));
    this->entityNum = entityNum;
    onPlatform = true;
    onTrampoline = true;
    isDead = false;
}

void PlayerObject::respawn(World* world) {
    isDead = true;
    setX(getCheckX());
    world->setCameraX(-640 + getCheckX());
    setY(getCheckY());
    world->setCameraY(getCheckY() - 360);
    // no need to set the x velocity
    setYVel(-.5);
    graphics->setUpsideDown(false);
    graphics->setCurrState(0);
    world->updateVolume(entityNum, getX(),
                        getY(), getW(),
                        getH());
}

PlayerObject::~PlayerObject() {
    delete graphics;
    delete input;
    delete sound;
    delete physics;

    return;
}
