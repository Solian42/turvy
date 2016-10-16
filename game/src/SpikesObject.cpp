#include "../include/SpikesObject.h"

SpikesObject::SpikesObject(int x, int y, bool orientation, TerrainGraphicsComponent *g) {
	location = {x, y, w, h};
	this->xFloat = (float)x;
	this->yFloat = (float)y;
	this->setOrientation(orientation);
	this->setSpikes(true);
	this->graphics = g;
	g->setGameObject(this);
	this->location = (g->getTextureRect(g->getCurrentSpirte()));
}