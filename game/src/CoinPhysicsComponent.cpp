#include "../include/CoinPhysicsComponent.h"

CoinPhysicsComponent::CoinPhysicsComponent() {}

bool CoinPhysicsComponent::checkThisCollision(SDL_Rect intersect){
	//if the intersect rect has x,y inside the coins rect range, this collision.
	if(intersect.x >= myCoin->getX()
		&& intersect.x <= myCoin->getX() + myCoin->getW()
		&& intersect.y >= myCoin->getY()
		&& intersect.y <= myCoin->getY() + myCoin->getH())
	{
		return true;
	}
	return false;
}

void CoinPhysicsComponent::update(World *world, int dt) {

    // if player collides with Coin
    temp = world->collideWithCoin(myCoin->playerObj);
    if (temp.first) {
    	if(checkThisCollision(temp.second)){
	        if (!myCoin->isEaten) {
	            world->setCoinCollision(true);
	            myCoin->isEaten = true;
	            // std::printf(coinObj->isEaten ? "true" : "false");
	        }
	    }
    }
}

CoinPhysicsComponent::~CoinPhysicsComponent() {}
