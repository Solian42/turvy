#include "../include/SpikesObject.h"

SpikesObject::SpikesObject(int x, int y, bool orientation, SpikesGraphicsComponent *g) {
	location = {x, y, 0, 0};
	this->xFloat = (float)x;
	this->yFloat = (float)y;
	this->setOrientation(orientation);
	this->graphics = g;
	g->setGameObject(this);
	this->location = (g->getTextureRect(g->getCurrentSprite()));
}

SpikesObject::~SpikesObject() {
	delete graphics;

	return;
}