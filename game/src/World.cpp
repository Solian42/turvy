#include "../include/World.h"

int World::transformX(int x) {
	return x;
}

int World::transformY(int y) {
	return (this->y - y);
}