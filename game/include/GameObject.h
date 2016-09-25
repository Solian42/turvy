#ifndef GAME_OBJECT_LIZARD
#define GAME_OBJECT_LIZARD

class GameObject {
	
	public:
	int x,y,velocity;
	GameObject(int x, int y, int velocity) {this->x = x; this->y = y; this->velocity = velocity;}
	void update();
	
	private:
	
};

#endif
